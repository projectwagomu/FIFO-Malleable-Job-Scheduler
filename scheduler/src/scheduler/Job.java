package scheduler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.net.Socket;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

public class Job extends Thread {
    private Path scriptPath;
    private Path scriptDir;
    private String jobType;
    public String jobClass;
    public int minNodes;
    public int maxNodes;
    public int numHost;
    public List<String> usingHosts;
    public ScriptManager manager;

    public Job(Path path, ScriptManager manager) {
        this.manager = manager;
        this.scriptPath = path;
        this.scriptDir = path.getParent();
        try (BufferedReader reader = new BufferedReader(new FileReader(path.toString()))) {
            String line;
            for (int i=0; i<5; i++) {
                line = reader.readLine();
                if (line.startsWith("#JOB_TYPE")) {
                    this.jobType = line.substring(line.indexOf(" ") + 1);
                } else if (line.startsWith("#JOB_CLASS")) {
                    this.jobClass = line.substring(line.indexOf(" ") + 1);
                } else if (line.startsWith("#MIN_NODES")) {
                    this.minNodes = Integer.parseInt(line.substring(line.indexOf(" ") + 1));
                } else if (line.startsWith("#MAX_NODES")) {
                    this.maxNodes = Integer.parseInt(line.substring(line.indexOf(" ") + 1));
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (this.jobType.equals("charm")) {
            this.minNodes++;
            this.maxNodes++;
        }
    }

    public boolean isExecutable() {
        return this.minNodes <= manager.availableHosts.size();
    }

    public void shrink(int decreasedNum) {
        List<String> currentHosts = new ArrayList<>();
        for (String h : this.usingHosts) {
            currentHosts.add(h);
        };
        this.usingHosts.subList(this.usingHosts.size()-decreasedNum, this.usingHosts.size()).clear();
        String[] unusedHosts = new String[decreasedNum];

        try {
            Socket socket = new Socket("localhost", 8081);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            out.println(this.scriptDir + ":" + "shrink" + ":" + this.jobType + ":" + currentHosts.toString() + ":" + String.valueOf(decreasedNum));
            unusedHosts = in.readLine().replaceAll("[\\[\\]\\s]", "").split(","); 
            String response = in.readLine();
            if (response.equals("success")) {
                System.out.println("shrink : " + this);
            }
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        manager.log.jobShrunk(scriptDir.toString(), Arrays.asList(unusedHosts));
        
        for (int i = 0; i < unusedHosts.length; i++) {
            usingHosts.remove(unusedHosts[i]);
            manager.availableHosts.add(unusedHosts[i]);
        }

        this.numHost = usingHosts.size();
    }

    public void expand(int increasedNum) {
        List<String> currentHosts = new ArrayList<>();
        for (String h : this.usingHosts) {
            currentHosts.add(h);
        };
        List<String> newHosts = new ArrayList<>();
        for (int i=0; i<increasedNum; i++) {
            String h = manager.availableHosts.poll();
            this.usingHosts.add(h);
            newHosts.add(h);
        }

        // Inform the logger of the expansion
        manager.log.jobExpand(scriptDir.toString(), newHosts);
        
        try {
            Socket socket = new Socket("localhost", 8081);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            out.println(this.scriptDir + ":" + "expand" + ":" + this.jobType + ":" + currentHosts.toString() + ":" + newHosts.toString());
            String response = in.readLine();
            if (response.equals("success")) {
                System.out.println("expand : " + this);
            }
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        this.numHost = usingHosts.size();
    }

    public void run() {
        System.out.println("available hosts: " + manager.availableHosts);
        System.out.println("run " + this);
        this.numHost = this.maxNodes;
        while(this.numHost > manager.availableHosts.size()) {
            this.numHost--;
        }
        this.usingHosts = new ArrayList<>();
        for (int i = 0; i < this.numHost; i++) {
            this.usingHosts.add(manager.availableHosts.poll());
        }
        System.out.println("using hosts: " + this.usingHosts);
        System.out.println("available hosts: " + manager.availableHosts); 
        String nodeFile = "nodeFile";
        File file = new File(this.scriptDir + "/" + nodeFile);
        try {
            if (!file.exists()) {
                file.createNewFile();
            }
            PrintWriter pw = new PrintWriter(file);
            if (this.jobType.equals("mpi")) {
                this.usingHosts.forEach(h -> pw.println(h + " slots=1")); 
            } else if (this.jobType.equals("charm")) {
                this.usingHosts.forEach(h -> {
                    if (h.equals(this.usingHosts.get(0))) return;
                    pw.println("host " + h);
                }); 
            } else if (this.jobType.equals("apgas")) {
                this.usingHosts.forEach(h -> pw.println(h)); 
            }
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        int nodes = this.jobType.equals("charm") ? (this.numHost-1) : this.numHost;
        String[] cmd = {
            "ssh",
            this.usingHosts.get(0),
            "NODES=" + nodes,
            "NODE_FILE=" + file,
            "SCRIPT_DIR=" + this.scriptDir,
            this.scriptPath.toString(),
//            ">", "_stdout.txt", "2>", "_stderr.txt"
        };
        System.out.println(Arrays.toString(cmd));
        
        // Log the start of the execution
        manager.log.jobStarted(scriptDir.toString(), usingHosts);
        
        try {
            Process process = Runtime.getRuntime().exec(cmd);
            ScriptManager.runningJobs.add(this);
            BufferedReader reader = new BufferedReader(new
                InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
              output.append(line + "\n");
            }
            reader.close();
            PrintWriter writer = new PrintWriter(this.scriptDir + "/result.txt");
//            System.out.println(output.toString());
            writer.print(output.toString());
            writer.close();
            // This job has officially completed
            System.out.println("Done: " + this);
            manager.log.jobTerminated(scriptDir.toString());
            ScriptManager.runningJobs.remove(this);
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.usingHosts.forEach(h -> manager.availableHosts.add(h));
        System.out.println("available hosts: " + manager.availableHosts);
        file.delete();
    }

    @Override
    public String toString() {
        return String.format("%s", scriptDir.getFileName());
    }

}
