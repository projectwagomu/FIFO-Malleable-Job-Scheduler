package scheduler;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

/**
 * Class in charge of recording all the events and keep them
 *
 * @author Patrick Finnerty
 *
 */
public class Logger {

	long startStamp;
	PrintWriter writer;

	public Logger() throws IOException {
		writer = new PrintWriter("scheduler_log.txt");
	}

	public void finished() {
		final long time = System.nanoTime() - startStamp;
		writer.println(time + "; all jobs completed");
		writer.flush();
		writer.close();
	}

	public synchronized void jobExpand(String jobName, List<String> additionalHosts) {
		final long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; expand; " + additionalHosts);
		writer.flush();
	}

	public synchronized void jobShrunk(String jobName, List<String> releasedHosts) {
		final long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; released; " + releasedHosts);
		writer.flush();
	}

	public synchronized void jobsSubmitted() {
		startStamp = System.nanoTime();
	}

	public synchronized void jobStarted(String jobName, List<String> hosts) {
		final long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; started; " + hosts);
		writer.flush();
	}

	public synchronized void jobTerminated(String jobName) {
		final long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; terminated");
		writer.flush();
	}
}
