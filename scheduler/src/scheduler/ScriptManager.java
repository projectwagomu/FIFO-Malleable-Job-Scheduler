package scheduler;

import java.util.List;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;

public class ScriptManager extends Thread {

  public static Queue<String> availableHosts = new ArrayDeque<>();
  public static List<Job> runningJobs = new ArrayList<>();
  static {
    for (int i = 0; i < 5; i++) {
      // piccolo00 ~ piccolo11
      availableHosts.add(String.format("piccolo%02d", i));
    }
  }

  public void run() {
    while (true) {
      try {
        Thread.sleep(5000);
        System.out.println("running jobs: " + runningJobs);
        if (Scheduler.jobQueue.size() > 0) {
          System.out.println("job queue: " + Scheduler.jobQueue);
          Job job = Scheduler.jobQueue.poll();
          while (!job.isExecutable()) {
            int releasableHosts = 0;
            for (Job j : runningJobs) {
              if (!j.jobClass.equals("malleable")) {
                continue;
              }
              releasableHosts += j.numHost - j.minNodes;
            }
            if (releasableHosts >= job.minNodes - availableHosts.size()) {
              shrinkJobs(releasableHosts);
            }
            Thread.sleep(5000);
          }
          job.start();
        } else {
          if (availableHosts.size() > 0) {
            expandJobs();
          }
          System.out.println("job queue: " + Scheduler.jobQueue);
        }
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }

  private void shrinkJobs(int requiredHosts) {
    for (Job j : runningJobs) {
      if (!j.jobClass.equals("malleable")) {
        continue;
      }
      j.shrink(Math.min(requiredHosts, j.numHost-j.minNodes));
      requiredHosts -= j.numHost - j.minNodes;
      if (requiredHosts <= 0) {
        break;
      }
    }
  }

  private void expandJobs() {
    for (Job j : runningJobs) {
      if (!j.jobClass.equals("malleable")) {
        continue;
      }
      if (j.numHost < j.maxNodes && availableHosts.size() > 0) {
        j.expand(Math.min(j.maxNodes - j.numHost, availableHosts.size()));
      }
    }
  }

}
