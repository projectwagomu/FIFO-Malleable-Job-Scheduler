package scheduler;

import java.util.List;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;

public class ScriptManager extends Thread {

	public Queue<String> availableHosts;
	public volatile boolean terminateFlag = false;
	public static List<Job> runningJobs = new ArrayList<>();

	public ScriptManager(String[] args) {
		availableHosts = new ArrayDeque<>();
		for (final String s : args) {
			availableHosts.add(s);
			System.out.println("added host " + s);
		}
	}

	public void run() {
		int noJobsRunningNoQueue = 0;
		while (noJobsRunningNoQueue < 5) {
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
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		System.out.println("Script Manager did not receive any jobs for while and will now stop");
		terminateFlag = true; // Used by the ScriptReceiver to stop
	}

	private void shrinkJobs(int requiredHosts) {
		for (Job j : runningJobs) {
			if (!j.jobClass.equals("malleable")) {
				continue;
			}
			if (j.numHost == j.minNodes) continue;
			int releaseHosts = Math.min(requiredHosts, j.numHost - j.minNodes);
			j.shrink(releaseHosts);
			requiredHosts -= releaseHosts;
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
