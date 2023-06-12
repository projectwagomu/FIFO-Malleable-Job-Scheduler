package scheduler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Job extends Thread {
	public String jobClass;
	private String jobType;
	public ScriptManager manager;
	public int maxNodes;
	public int minNodes;
	public int numHost;
	private final Path scriptDir;
	private final Path scriptPath;
	public List<String> usingHosts;

	public Job(Path path, ScriptManager manager) {
		this.manager = manager;
		scriptPath = path;
		scriptDir = path.getParent();
		try (BufferedReader reader = new BufferedReader(new FileReader(path.toString()))) {
			String line;
			for (int i = 0; i < 5; i++) {
				line = reader.readLine();
				if (line.startsWith("#JOB_TYPE")) {
					jobType = line.substring(line.indexOf(" ") + 1);
				} else if (line.startsWith("#JOB_CLASS")) {
					jobClass = line.substring(line.indexOf(" ") + 1);
				} else if (line.startsWith("#MIN_NODES")) {
					minNodes = Integer.parseInt(line.substring(line.indexOf(" ") + 1));
				} else if (line.startsWith("#MAX_NODES")) {
					maxNodes = Integer.parseInt(line.substring(line.indexOf(" ") + 1));
				}
			}
		} catch (final IOException e) {
			e.printStackTrace();
		}
		if (jobType.equals("charm")) {
			minNodes++;
			maxNodes++;
		}
	}

	public void expand(int increasedNum) {
		final List<String> currentHosts = new ArrayList<>();
		currentHosts.addAll(usingHosts);
		final List<String> newHosts = new ArrayList<>();
		for (int i = 0; i < increasedNum; i++) {
			final String h = manager.availableHosts.poll();
			usingHosts.add(h);
			newHosts.add(h);
		}

		// Inform the logger of the expansion
		manager.log.jobExpand(scriptDir.toString(), newHosts);

		try {
			final Socket socket = new Socket("localhost", 8081);
			final BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			final PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			out.println(scriptDir + ":" + "expand" + ":" + jobType + ":" + currentHosts.toString() + ":"
					+ newHosts.toString());
			final String response = in.readLine();
			if (response.equals("success")) {
				System.out.println("expand : " + this);
			}
			socket.close();
		} catch (final Exception e) {
			e.printStackTrace();
		}

		numHost = usingHosts.size();
	}

	public boolean isExecutable() {
		return minNodes <= manager.availableHosts.size();
	}

	@Override
	public void run() {
		System.out.println("available hosts: " + manager.availableHosts);
		System.out.println("run " + this);
		numHost = maxNodes;
		while (numHost > manager.availableHosts.size()) {
			numHost--;
		}
		usingHosts = new ArrayList<>();
		for (int i = 0; i < numHost; i++) {
			usingHosts.add(manager.availableHosts.poll());
		}
		System.out.println("using hosts: " + usingHosts);
		System.out.println("available hosts: " + manager.availableHosts);
		final String nodeFile = "nodeFile";
		final File file = new File(scriptDir + "/" + nodeFile);
		try {
			if (!file.exists()) {
				file.createNewFile();
			}
			final PrintWriter pw = new PrintWriter(file);
			if (jobType.equals("mpi")) {
				usingHosts.forEach(h -> pw.println(h + " slots=1"));
			} else if (jobType.equals("charm")) {
				usingHosts.forEach(h -> {
					if (h.equals(usingHosts.get(0))) {
						return;
					}
					pw.println("host " + h);
				});
			} else if (jobType.equals("apgas")) {
				usingHosts.forEach(h -> pw.println(h));
			}
			pw.close();
		} catch (final IOException e) {
			e.printStackTrace();
		}
		final int nodes = jobType.equals("charm") ? (numHost - 1) : numHost;
		final String[] cmd = { "ssh", usingHosts.get(0), "NODES=" + nodes, "NODE_FILE=" + file,
				"SCRIPT_DIR=" + scriptDir, scriptPath.toString(),
//            ">", "_stdout.txt", "2>", "_stderr.txt"
		};
		System.out.println(Arrays.toString(cmd));

		// Log the start of the execution
		manager.log.jobStarted(scriptDir.toString(), usingHosts);

		try {
			final Process process = Runtime.getRuntime().exec(cmd);
			ScriptManager.runningJobs.add(this);
			final BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
			final StringBuilder output = new StringBuilder();
			String line;
			while ((line = reader.readLine()) != null) {
				output.append(line + "\n");
			}
			reader.close();
			final PrintWriter writer = new PrintWriter(scriptDir + "/result.txt");
//            System.out.println(output.toString());
			writer.print(output.toString());
			writer.close();
			// This job has officially completed
			System.out.println("Done: " + this);
			manager.log.jobTerminated(scriptDir.toString());
			ScriptManager.runningJobs.remove(this);
		} catch (final IOException e) {
			e.printStackTrace();
		}
		usingHosts.forEach(h -> manager.availableHosts.add(h));
		System.out.println("available hosts: " + manager.availableHosts);
		file.delete();
	}

	public void shrink(int decreasedNum) {
		final List<String> currentHosts = new ArrayList<>();
		currentHosts.addAll(usingHosts);
		usingHosts.subList(usingHosts.size() - decreasedNum, usingHosts.size()).clear();
		// String[] unusedHosts = new String[decreasedNum];
		final ArrayList<String> releasedHosts = new ArrayList<>();

		try {
			final Socket socket = new Socket("localhost", 8081);
			final BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			final PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			out.println(scriptDir + ":" + "shrink" + ":" + jobType + ":" + currentHosts.toString() + ":"
					+ String.valueOf(decreasedNum));
			final String[] unusedHosts = in.readLine().replaceAll("[\\[\\]\\s]", "").split(",");

			// Remove any hostname which does not belong to the list of host
			// This avoids including connection error traces
			for (final String h : unusedHosts) {
				if (manager.allHosts.contains(h)) {
					releasedHosts.add(h);
				}
			}

			final String response = in.readLine();
			if (response.equals("success")) {
				System.out.println("shrink : " + this);
			}
			socket.close();
		} catch (final Exception e) {
			e.printStackTrace();
		}

		manager.log.jobShrunk(scriptDir.toString(), releasedHosts);

		for (final String h : releasedHosts) {
			usingHosts.remove(h);
			manager.availableHosts.add(h);
		}

		numHost = usingHosts.size();
	}

	@Override
	public String toString() {
		return String.format("%s", scriptDir.getFileName());
	}

}
