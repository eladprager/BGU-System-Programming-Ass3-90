package bgu.spl.net.impl.Frames.ServerToClient;

public class ConnectedFrame {

    String msg;
    double version;

    public ConnectedFrame(double version) {
        this.version = version;
    }

    public String send() {
        msg = "CONNECTED\nversion:"+version+"\n\n^@";
//        System.out.println(msg);
        return (msg);
    }

}
