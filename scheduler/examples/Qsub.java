import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Qsub {
  public static void main(String[] args) {
    try {
      Socket socket = new Socket("localhost", 8080);
      // 入出力ストリームを取得
      BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
      String script = args[0];
      // サーバーに送信
      out.println(script);
      // サーバーからのメッセージを受け取る
      String response = in.readLine();
      System.out.println(response);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
