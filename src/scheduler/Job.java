package scheduler;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Job extends Thread {
    private String scriptPath;
    private String jobType;
    private String jobClass;
    private int minNodes;
    private int maxNodes;

    public Job(String path) {
        this.scriptPath = path;
        try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
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
        // System.out.println("jobType: " + this.jobType);
        // System.out.println("jobClass: " + this.jobClass);
        // System.out.println("minNodes: " + this.minNodes);
        // System.out.println("maxNodes: " + this.maxNodes);
    }

    public boolean isExecutable() {
        return this.minNodes <= ScriptManager.availableHosts.size();
    }

    public void run() {
        Pattern p = Pattern.compile("(.*)/");
        Matcher m = p.matcher(this.scriptPath);
        String scriptDir = null;
        if (m.find()) {
            scriptDir = m.group(1);
        }
        // System.out.println("scriptDir:" + scriptDir);
        System.out.println("available hosts: " + ScriptManager.availableHosts);
        System.out.println("run " + this.scriptPath);
        int numHost = this.maxNodes;
        while(numHost > ScriptManager.availableHosts.size()) {
            numHost--;
        }
        List<String> hosts = new ArrayList<>();
        for (int i = 0; i < numHost; i++) {
            hosts.add(ScriptManager.availableHosts.poll());
        }
        System.out.println("using hosts: " + hosts);
        System.out.println("available hosts: " + ScriptManager.availableHosts); 
        String nodeFile = "nodeFile";
        File file = new File(scriptDir + "/" + nodeFile);
        try {
            if (!file.exists()) {
                file.createNewFile();
            }
            PrintWriter pw = new PrintWriter(file);
            if (this.jobType.equals("mpi")) {
                hosts.forEach(h -> pw.println(h + " slots=1")); 
            } else if (this.jobType.equals("charm")) {
                hosts.forEach(h -> {
                    if (h.equals(hosts.get(0))) return;
                    pw.println("host " + h);
                }); 
            }
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        String[] cmd = {
            "ssh",
            hosts.get(0),
            "NODES=" + numHost,
            "NODE_FILE=" + file,
            "SCRIPT_DIR=" + scriptDir,
            this.scriptPath,
        };
        try {
            Process process = Runtime.getRuntime().exec(cmd);
            ScriptManager.runningJobs.add(this.scriptPath);
            BufferedReader reader = new BufferedReader(new
                InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
              output.append(line + "\n");
            }
            reader.close();
            PrintWriter writer = new PrintWriter(scriptDir + "/result.txt");
            writer.print(output.toString());
            writer.close();
            System.out.println("Done: " + scriptPath);
            ScriptManager.runningJobs.remove(this.scriptPath); 
        } catch (IOException e) {
            e.printStackTrace();
        }
        hosts.forEach(h -> ScriptManager.availableHosts.add(h));
        System.out.println("available hosts: " + ScriptManager.availableHosts);
        file.delete();
    }

}