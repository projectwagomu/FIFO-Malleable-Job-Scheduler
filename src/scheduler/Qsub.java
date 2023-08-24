package scheduler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Qsub {
	public static void main(String[] args) {
		Socket socket = null;
		try {
			socket = new Socket("localhost", 8080);
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			String script = args[0];
			// send the script
			out.println(script);
			// receive messages
			String response = in.readLine();
			System.out.println(response);
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
