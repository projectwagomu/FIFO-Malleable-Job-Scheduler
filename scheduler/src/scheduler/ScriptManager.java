package scheduler;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Queue;

public class ScriptManager extends Thread {

	public static List<Job> runningJobs = new ArrayList<>();
	public HashSet<String> allHosts;
	public Queue<String> availableHosts;
	public Logger log;

	public volatile boolean terminateFlag = false;

	public ScriptManager(String[] args) {
		availableHosts = new ArrayDeque<>();
		allHosts = new HashSet<>();

		for (final String s : args) {
			availableHosts.add(s);
			allHosts.add(s);
			System.out.println("added host " + s);
		}
		try {
			log = new Logger();
		} catch (final Exception e) {
			e.printStackTrace();
		}
	}

	private void expandJobs() {
		for (final Job j : runningJobs) {
			if (!j.jobClass.equals("malleable")) {
				continue;
			}
			if (j.numHost < j.maxNodes && availableHosts.size() > 0) {
				j.expand(Math.min(j.maxNodes - j.numHost, availableHosts.size()));
			}
		}
	}

	@Override
	public void run() {
		int noJobsRunningNoQueue = 0;
		boolean firstJobs = true;
		while (noJobsRunningNoQueue < 5) {
			try {
				Thread.sleep(5000);
				System.out.println("running jobs: " + runningJobs);
				if (Scheduler.jobQueue.size() > 0) {

					if (firstJobs) { // Set the start timer for the logger when jobs are first received
						log.jobsSubmitted();
						firstJobs = false;
					}
					System.out.println("job queue: " + Scheduler.jobQueue);
					final Job job = Scheduler.jobQueue.poll();
					while (!job.isExecutable()) {
						int releasableHosts = 0;
						for (final Job j : runningJobs) {
							if (!j.jobClass.equals("malleable")) {
								continue;
							}
							releasableHosts += j.numHost - j.minNodes;
						}
						if (releasableHosts >= job.minNodes - availableHosts.size()) {
							shrinkJobs(job.minNodes - availableHosts.size());
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

				if (runningJobs.isEmpty() && Scheduler.jobQueue.isEmpty()) {
					noJobsRunningNoQueue++;
				}
			} catch (final InterruptedException e) {
				e.printStackTrace();
			}
		}
		System.out.println("Script Manager did not receive any jobs for while and will now stop");
		log.finished();
		terminateFlag = true; // Used by the ScriptReceiver to stop
	}

	private void shrinkJobs(int requiredHosts) {
		for (final Job j : runningJobs) {
			if (!j.jobClass.equals("malleable") || (j.numHost == j.minNodes)) {
				continue;
			}
			final int releaseHosts = Math.min(requiredHosts, j.numHost - j.minNodes);
			j.shrink(releaseHosts);
			requiredHosts -= releaseHosts;
			if (requiredHosts <= 0) {
				break;
			}
		}
	}

}
