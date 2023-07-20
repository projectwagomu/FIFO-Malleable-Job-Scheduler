package scheduler;

import java.io.IOException;
import java.util.ArrayDeque;
import java.util.Queue;

public class Scheduler {

	public static Queue<Job> jobQueue = new ArrayDeque<>();

	public static void main(String[] args) {

		if (args == null || args.length == 0) {
			System.out.println("needed hosts as args");
			return;
		}
		ScriptManager manager = null;
		try {
			manager = new ScriptManager(args[0]);
		} catch (IOException e) {
			System.err.println("Error while trying to open file " + args[0] + ", quiting");
			return;
		}
		final ScriptReceiver receiver = new ScriptReceiver(manager);

		receiver.start();
		manager.run(); // Automatically returns after a while without any submissions
		System.exit(0);
	}

}
