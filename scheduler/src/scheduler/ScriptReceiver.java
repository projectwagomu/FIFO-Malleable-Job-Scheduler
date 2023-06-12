package scheduler;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Path;

public class ScriptReceiver extends Thread {

	ScriptManager manager;

	public ScriptReceiver(ScriptManager manager) {
		this.manager = manager;
	}

	@Override
	public void run() {
		try {
			final ServerSocket serverSocket = new ServerSocket(8080);
			while (!manager.terminateFlag) {
				final Socket clientSocket = serverSocket.accept();
				final BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
				final PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				final String script = in.readLine();
				Scheduler.jobQueue.add(new Job(Path.of(script), manager));
				out.println(script + " received.");
			}
			serverSocket.close();
		} catch (final Exception e) {
			e.printStackTrace();
		}
	}

}
