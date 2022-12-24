package scheduler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ScriptExecutor extends Thread {

    private String script;
    private List<String> hosts = new ArrayList<>();

    public ScriptExecutor(String script, String... hosts) {
        this.script = script;
        for (String host: hosts) {
            this.hosts.add(host);
        }
    }

    public void run() {
        System.out.println("run " + script);
        try {
            Process process = Runtime.getRuntime().exec("ssh " + hosts.get(0) + " " + script);
            BufferedReader reader = new BufferedReader(new
                InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
              output.append(line + "\n");
            }
            reader.close();
            Pattern p = Pattern.compile("([^/]+)$");
            Matcher m = p.matcher(script);
            while(m.find()) {
                String result = m.group();
                PrintWriter writer = new PrintWriter("examples/" + result + ".txt");
                writer.print(output.toString());
                writer.close();
                System.out.println("Done: " + result);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
