package middlelayer;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;
import java.util.ArrayList;

public class Main {
  static String workingDir = System.getProperty("user.dir");
  public static void main(String[] args) {
    System.out.println("workingDir: " + workingDir);
    try {
      ServerSocket serverSocket = new ServerSocket(8081);
      while(true) {
        Socket clientSocket = serverSocket.accept();
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
        String[] params = in.readLine().split(":");
        for (String p : params) {
          System.out.println(p);
        }
        String scriptDir = params[0];
        String operation = params[1];
        String jobType = params[2];
        String[] currentHosts = params[3].replaceAll("[\\[\\]\\s]", "").split(",");
        int decreasedNum = 0;
        String[] newHosts = null;
        if (operation.equals("expand")) {
          newHosts = params[4].replaceAll("[\\[\\]\\s]", "").split(",");
          ProcessBuilder builder;
          if (jobType.equals("apgas")) {
            builder = new ProcessBuilder("ssh", currentHosts[0], "java -cp " + workingDir "/shrink_expand/apgas/ Client expand", String.valueOf(newHosts.length), String.join(" ", newHosts));
          } else {
            String nodeFile = "nodeFile";
            File file = new File(scriptDir + "/" + nodeFile);
            try {
              if (!file.exists()) {
                file.createNewFile();
              }
              PrintWriter pw = new PrintWriter(file);
              for (int i=0; i<currentHosts.length; i++) {
                if (i==0) continue;
                pw.println("host " + currentHosts[i]);
              }
              for (int i=0; i<newHosts.length; i++) {
                pw.println("host " + newHosts[i]);
              }
              pw.close();
            } catch (IOException e) {
              e.printStackTrace();
            }
            builder = new ProcessBuilder(workingDir + "/shrink_expand/charm/client", currentHosts[0], "1234", String.valueOf(currentHosts.length-1), String.valueOf(currentHosts.length-1+newHosts.length));
          }
          Process process = builder.start();
          BufferedReader reader = new BufferedReader(new
          InputStreamReader(process.getInputStream()));
          String line;
          while((line = reader.readLine()) != null) {
            System.out.println(line);
          }
          process.waitFor();
          out.println("success");
        } else if (operation.equals("shrink")) {
          decreasedNum = Integer.parseInt(params[4]);
          if (jobType.equals("apgas")) {
            List<String> unusedHosts = new ArrayList<>();
            ProcessBuilder builder = new ProcessBuilder("ssh", currentHosts[0], "java -cp " + workingDir + "/shrink_expand/apgas/ Client shrink", String.valueOf(decreasedNum));
            Process process = builder.start();
            BufferedReader reader = new BufferedReader(new
            InputStreamReader(process.getInputStream()));
            String line;
            while((line = reader.readLine()) != null) {
              unusedHosts.add(line);
              System.out.println(line);
            }
            process.waitFor();
            out.println(unusedHosts.toString());
            out.println("success");
          } else if (jobType.equals("charm")) {
            List<String> unusedHosts = new ArrayList<>();
            for (int i = 0; i < decreasedNum; i++) {
              unusedHosts.add(currentHosts[currentHosts.length-1 - i]);
            }
            String nodeFile = "nodeFile";
            File file = new File(scriptDir + "/" + nodeFile);
            try {
              if (!file.exists()) {
                file.createNewFile();
              }
              PrintWriter pw = new PrintWriter(file);
              for (int i=0; i<currentHosts.length-unusedHosts.size(); i++) {
                if (i==0) continue;
                pw.println("host " + currentHosts[i]);
              }
              pw.close();
            } catch (IOException e) {
              e.printStackTrace();
            }
            ProcessBuilder builder = new ProcessBuilder(workingDir + "/shrink_expand/charm/client", currentHosts[0], "1234", String.valueOf(currentHosts.length-1), String.valueOf(currentHosts.length-1-decreasedNum));
            Process process = builder.start();
            BufferedReader reader = new BufferedReader(new
            InputStreamReader(process.getInputStream()));
            String line;
            while((line = reader.readLine()) != null) {
              System.out.println(line);
            }
            process.waitFor();
            out.println(unusedHosts.toString());
            out.println("success");
          }
        }
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
