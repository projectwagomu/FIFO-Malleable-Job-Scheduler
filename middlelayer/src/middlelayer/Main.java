package middlelayer;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Main {
	static String workingDir = System.getProperty("user.dir");

	public static void main(String[] args) {
		System.out.println("workingDir: " + workingDir);
		try {
			@SuppressWarnings("resource")
			final ServerSocket serverSocket = new ServerSocket(8081);
			while (true) {
				final Socket clientSocket = serverSocket.accept();
				final BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
				final PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				final String[] params = in.readLine().split(":");
				for (final String p : params) {
					System.out.println(p);
				}
				final String scriptDir = params[0];
				final String operation = params[1];
				final String jobType = params[2];
				final String[] currentHosts = params[3].replaceAll("[\\[\\]\\s]", "").split(",");
				int decreasedNum = 0;
				String[] newHosts = null;
				if (operation.equals("expand")) {
					newHosts = params[4].replaceAll("[\\[\\]\\s]", "").split(",");
					ProcessBuilder builder;
					if (jobType.equals("apgas")) {
						builder = new ProcessBuilder("ssh", currentHosts[0],
								"java -cp " + workingDir + "/shrink_expand/apgas/ Client expand",
								String.valueOf(newHosts.length), String.join(" ", newHosts));
					} else {
						final String nodeFile = "nodeFile";
						final File file = new File(scriptDir + "/" + nodeFile);
						try {
							if (!file.exists()) {
								file.createNewFile();
							}
							final PrintWriter pw = new PrintWriter(file);
							for (int i = 0; i < currentHosts.length; i++) {
								if (i == 0) {
									continue;
								}
								pw.println("host " + currentHosts[i]);
							}
							for (final String newHost : newHosts) {
								pw.println("host " + newHost);
							}
							pw.close();
						} catch (final IOException e) {
							e.printStackTrace();
						}
						builder = new ProcessBuilder(workingDir + "/shrink_expand/charm/client", currentHosts[0],
								"1234", String.valueOf(currentHosts.length - 1),
								String.valueOf(currentHosts.length - 1 + newHosts.length));
					}
					final Process process = builder.start();
					final BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
					String line;
					while ((line = reader.readLine()) != null) {
						System.out.println(line);
					}
					process.waitFor();
					out.println("success");
				} else if (operation.equals("shrink")) {
					decreasedNum = Integer.parseInt(params[4]);
					if (jobType.equals("apgas")) {
						final List<String> unusedHosts = new ArrayList<>();
						final ProcessBuilder builder = new ProcessBuilder("ssh", currentHosts[0],
								"java -cp " + workingDir + "/shrink_expand/apgas/ Client shrink",
								String.valueOf(decreasedNum));
						final Process process = builder.start();
						final BufferedReader reader = new BufferedReader(
								new InputStreamReader(process.getInputStream()));
						String line;
						while ((line = reader.readLine()) != null) {
							unusedHosts.add(line);
							System.out.println(line);
						}
						process.waitFor();
						out.println(unusedHosts.toString());
						out.println("success");
					} else if (jobType.equals("charm")) {
						final List<String> unusedHosts = new ArrayList<>();
						for (int i = 0; i < decreasedNum; i++) {
							unusedHosts.add(currentHosts[currentHosts.length - 1 - i]);
						}
						final String nodeFile = "nodeFile";
						final File file = new File(scriptDir + "/" + nodeFile);
						try {
							if (!file.exists()) {
								file.createNewFile();
							}
							final PrintWriter pw = new PrintWriter(file);
							for (int i = 0; i < currentHosts.length - unusedHosts.size(); i++) {
								if (i == 0) {
									continue;
								}
								pw.println("host " + currentHosts[i]);
							}
							pw.close();
						} catch (final IOException e) {
							e.printStackTrace();
						}
						final ProcessBuilder builder = new ProcessBuilder(workingDir + "/shrink_expand/charm/client",
								currentHosts[0], "1234", String.valueOf(currentHosts.length - 1),
								String.valueOf(currentHosts.length - 1 - decreasedNum));
						final Process process = builder.start();
						final BufferedReader reader = new BufferedReader(
								new InputStreamReader(process.getInputStream()));
						String line;
						while ((line = reader.readLine()) != null) {
							System.out.println(line);
						}
						process.waitFor();
						out.println(unusedHosts.toString());
						out.println("success");
					}
				}
			}
		} catch (final Exception e) {
			e.printStackTrace();
		}
	}

}
