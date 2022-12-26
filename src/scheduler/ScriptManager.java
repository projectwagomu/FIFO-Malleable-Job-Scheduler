package scheduler;

import java.util.List;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;

public class ScriptManager extends Thread {

  public static Queue<String> availableHosts = new ArrayDeque<>();
  public static List<String> runningJobs = new ArrayList<>();
  static {
    for (int i = 0; i < 10; i++) {
      // piccolo00 ~ piccolo09
      availableHosts.add(String.format("piccolo%02d", i));
    }
  }

  public void run() {
    while (true) {
      try {
        Thread.sleep(5000);
        System.out.println("running jobs: " + runningJobs);
        if (Scheduler.jobQueue.size() > 0) {
          System.out.println("job queue : " + Scheduler.jobQueue);
          Job job = new Job(Scheduler.jobQueue.poll());
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
