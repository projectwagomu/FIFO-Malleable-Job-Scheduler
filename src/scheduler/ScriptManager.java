package scheduler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayDeque;
import java.util.Queue;

public class ScriptManager extends Thread {
  Queue<String> jobQueue;

  public ScriptManager(Queue<String> jobQueue) {
    this.jobQueue = jobQueue;
  }

  public void run() {
    while (true) {
      try {
        Thread.sleep(5000);
        if (jobQueue.size() > 0) {
          System.out.println("job queue = " + jobQueue); 
          String script = jobQueue.poll();
          ScriptExecutor executor = new ScriptExecutor(script);
          executor.start();
        } else {
          System.out.println("job queue = " + jobQueue);
        }
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}
