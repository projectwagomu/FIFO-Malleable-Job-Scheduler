import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;
import java.net.ConnectException;
import java.util.concurrent.TimeUnit;

public class Client {
  public static void main(String[] args) {
    // connect to the server socket
    while (true) {
      try (Socket socket = new Socket("localhost", 8080);
        PrintWriter writer = new PrintWriter(socket.getOutputStream(), true)) {
        String str = new String();
        for (int i = 0; i < args.length; i++) {
          str += (args[i] + " ");
        }
        writer.println(str);
        if (args[0].equals("shrink")) {
          BufferedReader reader;
          reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
          for (int i = 0; i < Integer.parseInt(args[1]); i++) {
            String line = reader.readLine();
            System.out.println(line);
          }
        }
        return;
      } catch (ConnectException e) {
        System.out.println("ConnectionError - try again in one second");
        try {
          TimeUnit.SECONDS.sleep(1);
        } catch (InterruptedException ie) {
          ie.printStackTrace();
        }
        continue;
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
  }
}