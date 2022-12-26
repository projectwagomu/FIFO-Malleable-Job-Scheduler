package scheduler;

import java.util.ArrayDeque;
import java.util.Queue;

public class ScriptManager extends Thread {

  public ScriptManager() {

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
        if (Scheduler.jobQueue.size() > 0) {
          System.out.println("job queue : " + Scheduler.jobQueue);
          Job job = new Job(Scheduler.jobQueue.poll(), availableHosts);
          while (!job.isExecutable()) {
            System.out.println("waiting...");
            Thread.sleep(5000);
          }
          job.start();
        } else {
          System.out.println("job queue : " + Scheduler.jobQueue);
        }
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}
