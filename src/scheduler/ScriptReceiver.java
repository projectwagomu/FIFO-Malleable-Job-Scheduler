package scheduler;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Queue;

public class ScriptReceiver extends Thread {
  Queue<String> jobQueue;

  public ScriptReceiver(Queue<String> jobQueue) {
    this.jobQueue = jobQueue;
  }

  public void run() {
    try {
      ServerSocket serverSocket = new ServerSocket(8080);
      while (true) {
        Socket clientSocket = serverSocket.accept();
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
        String script = in.readLine();
        jobQueue.add(script);
        out.println(script + " received.");
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
