package scheduler;

import java.util.ArrayDeque;
import java.util.Queue;

public class Scheduler {

  public static Queue<Job> jobQueue = new ArrayDeque<>();
  public static void main(String[] args) {
    ScriptReceiver receiver = new ScriptReceiver();
    ScriptManager manager = new ScriptManager();

    receiver.start();
    manager.start();
  }

}
