package scheduler;

import java.util.ArrayDeque;
import java.util.Queue;

public class ScriptManager extends Thread {
  Queue<String> jobQueue;

  public ScriptManager(Queue<String> jobQueue) {
    this.jobQueue = jobQueue;
  }

  private void printJobQueue() {
    System.out.println("job queue : " + this.jobQueue);
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
          printJobQueue();
          Job job = new Job(jobQueue.poll(), availableHosts);
          while (job.getMaxNodes() > availableHosts.size()) {
            Thread.sleep(5000);
          }
          job.start();
        } else {
          printJobQueue();
        }
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}
