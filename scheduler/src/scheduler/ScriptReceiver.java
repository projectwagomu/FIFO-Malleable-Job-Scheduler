package scheduler;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Path;

public class ScriptReceiver extends Thread {

  public void run() {
    try {
      ServerSocket serverSocket = new ServerSocket(8080);
      while (true) {
        Socket clientSocket = serverSocket.accept();
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
        String script = in.readLine();
        Scheduler.jobQueue.add(Path.of(script));
        out.println(script + " received.");
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
  
}