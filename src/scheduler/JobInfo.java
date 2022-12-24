package scheduler;

public class JobInfo {
    private String script;
    private int numHosts;

    public JobInfo(String path) {
        //todo: get job information from script file.
        this.script = path;
        this.numHosts = 1;
    }

    public String getScript() {
        return this.script;
    }

    public int getNumHosts() {
        return this.numHosts;
    }
}