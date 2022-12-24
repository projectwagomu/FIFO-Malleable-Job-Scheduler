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
    Queue<String> availableHosts = new ArrayDeque<>();
    for (int i = 0; i < 10; i++) {
      // piccolo00 ~ piccolo09
      availableHosts.add(String.format("piccolo%02d", i));
    }

    while (true) {
      try {
        Thread.sleep(5000);
        if (jobQueue.size() > 0) {
          System.out.println("job queue = " + jobQueue); 
          JobInfo jobInfo = new JobInfo(jobQueue.poll());
          ScriptExecutor executor = new ScriptExecutor(jobInfo.getScript(), availableHosts.poll());
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
