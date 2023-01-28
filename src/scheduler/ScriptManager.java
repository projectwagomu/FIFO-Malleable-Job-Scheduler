package scheduler;

import java.util.List;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;

public class ScriptManager extends Thread {

  public static Queue<String> availableHosts = new ArrayDeque<>();
  public static List<Job> runningJobs = new ArrayList<>();
  static {
    for (int i = 4; i < 8; i++) {
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
            if (shrinkJobs(job.minNodes - availableHosts.size())) {
              break;
            }
            System.out.println("waiting...");
            Thread.sleep(5000);
          }
          job.start();
        } else {
          if (availableHosts.size() > 0) {
            expandJobs();
          }
          System.out.println("job queue : " + Scheduler.jobQueue);
        }
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }

  private boolean shrinkJobs(int requiredHosts) {
    List<Job> malleableJobs = new ArrayList<>();
    for (Job j : runningJobs) {
      if (j.jobClass.equals("malleable")) {
        malleableJobs.add(j);
      }
    }
    int emptyHosts = 0;
    for (Job j : malleableJobs) {
      emptyHosts += j.numHost - j.minNodes;
    }
    if (requiredHosts > emptyHosts) {
      // 実行中のmalleableジョブを縮小しても次のジョブを実行できない場合，なにもしない．
      return false;
    } else {
      for (Job j : malleableJobs) {
        j.shrink(Math.min(requiredHosts, j.numHost-j.minNodes));
        requiredHosts -= j.numHost - j.minNodes;
        if (requiredHosts <= 0) {
          break;
        }
      }
      return true;
    }
  }

  private void expandJobs() {
    List<Job> malleableJobs = new ArrayList<>();
    for (Job j : runningJobs) {
      if (j.jobClass.equals("malleable")) {
        malleableJobs.add(j);
      }
    }
    for (Job j : malleableJobs) {
      if (j.numHost < j.maxNodes && availableHosts.size() > 0) {
        j.expand(Math.min(j.maxNodes - j.numHost, availableHosts.size()));
      }
    }
  }
}
