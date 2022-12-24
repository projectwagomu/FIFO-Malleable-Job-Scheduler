package scheduler;

import java.util.ArrayDeque;
import java.util.Queue;

public class Scheduler {
  public static void main(String[] args) {
    Queue<String> jobQueue = new ArrayDeque<>();

    ScriptReceiver receiver = new ScriptReceiver(jobQueue);
    ScriptManager manager = new ScriptManager(jobQueue);

    receiver.start();
    manager.start();
  }
}
