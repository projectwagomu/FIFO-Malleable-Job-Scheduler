package scheduler;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

/**
 * Class in charge of recording all the events and keep them 
 * @author Patrick Finnerty
 *
 */
public class Logger {

	PrintWriter writer;
	long startStamp;
	
	public Logger () throws IOException {
		writer = new PrintWriter("scheduler_log.txt");
	}
	
	public synchronized void jobsSubmitted() {
		startStamp = System.nanoTime();
	}
	
	public synchronized void jobStarted(String jobName, List<String> hosts) {
		long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; started; " + hosts);
	}
	
	public synchronized void jobShrunk(String jobName, List<String> releasedHosts) {
		long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; released; " + releasedHosts);
	}
	
	public synchronized void jobExpand(String jobName, List<String> additionalHosts) {
		long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; expand; " + additionalHosts);
	}
	
	public synchronized void jobTerminated(String jobName) {
		long time = System.nanoTime() - startStamp;
		writer.println(time + ";" + jobName + "; terminated");
	}
	
	public void finished() {
		long time = System.nanoTime() - startStamp;
		writer.println(time + "; all jobs completed");
		writer.flush();
		writer.close();
	}
}
