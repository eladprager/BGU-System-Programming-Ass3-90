package bgu.spl.net.impl.Frames.ClientToServer;

public class ConnectFrame {

    String msg;
    int version;

    public ConnectFrame(int version) {
        this.version = version;
    }


    void send() {
        msg = "CONNECTED\n version:"+version+"\n\n ^@";
        System.out.println(msg);
    }
}
