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
  public static void main(String[] args) {
    try {
      ServerSocket serverSocket = new ServerSocket(8081);
      while(true) {
        Socket clientSocket = serverSocket.accept();
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
        String[] jobInfo = in.readLine().split(":");
        for (String s : jobInfo) {
          System.out.println(s);
        }
        if (jobInfo[1].equals("expand")) {
          String[] currentHosts = jobInfo[3].replaceAll("[\\[\\]\\s]", "").split(","); 
          String[] newHosts = jobInfo[4].replaceAll("[\\[\\]\\s]", "").split(",");
          ProcessBuilder builder;
          if (jobInfo[2].equals("apgas")) {
            builder = new ProcessBuilder("ssh", currentHosts[0], "java -cp /home/takaoka/scheduler/middlelayer/shrink_expand/apgas/ Client expand", String.valueOf(newHosts.length), String.join(" ", newHosts));
          } else {
            builder = new ProcessBuilder("/home/takaoka/scheduler/middlelayer/shrink_expand/charm/client", currentHosts[0], "1234", String.valueOf(currentHosts.length-1), String.valueOf(currentHosts.length-1+newHosts.length));
          }
          Process process = builder.start();
          BufferedReader reader = new BufferedReader(new
          InputStreamReader(process.getInputStream()));
          String line;
          while((line = reader.readLine()) != null) {
            System.out.println(line);
          }
          process.waitFor();
          out.println("ok");
        } else if (jobInfo[1].equals("shrink")) {
          String[] currentHosts = jobInfo[3].replaceAll("[\\[\\]\\s]", "").split(","); 
          int decreasedNum = Integer.parseInt(jobInfo[4]);
          if (jobInfo[2].equals("apgas")) {
            List<String> unusedHosts = new ArrayList<>();
            ProcessBuilder builder = new ProcessBuilder("ssh", currentHosts[0], "java -cp /home/takaoka/scheduler/middlelayer/shrink_expand/apgas/ Client shrink", String.valueOf(decreasedNum));
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
            out.println("ok");
          } else if (jobInfo[2].equals("charm")) {
            List<String> unusedHosts = new ArrayList<>();
            for (int i = 0; i < decreasedNum; i++) {
              unusedHosts.add(currentHosts[currentHosts.length-1 - i]);
            }
            String nodeFile = "nodeFile";
            File file = new File(jobInfo[0] + "/" + nodeFile);
            try {
              if (!file.exists()) {
                file.createNewFile();
              }
              PrintWriter pw = new PrintWriter(file);
              for (int i=0; i<currentHosts.length; i++) {
                if (i==0) continue;
                pw.println("host " + currentHosts[i]);
              }
              pw.close();
            } catch (IOException e) {
              e.printStackTrace();
            }
            ProcessBuilder builder = new ProcessBuilder("/home/takaoka/scheduler/middlelayer/shrink_expand/charm/client", currentHosts[0], "1234", String.valueOf(currentHosts.length-1), String.valueOf(currentHosts.length-1-decreasedNum));
            Process process = builder.start();
            BufferedReader reader = new BufferedReader(new
            InputStreamReader(process.getInputStream()));
            String line;
            while((line = reader.readLine()) != null) {
              System.out.println(line);
            }
            process.waitFor();
            out.println(unusedHosts.toString());
            out.println("ok");
          }
        }
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
