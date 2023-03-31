package scheduler;

import java.util.ArrayDeque;
import java.util.Queue;

public class Scheduler {

  public static Queue<Job> jobQueue = new ArrayDeque<>();
  public static void main(String[] args) {

    if (args == null  || args.length == 0) {
      System.out.println("needed hosts as args");
      return;
    }

    ScriptManager manager = new ScriptManager(args);
    ScriptReceiver receiver = new ScriptReceiver(manager);

    receiver.start();
    manager.start();
  }

}
