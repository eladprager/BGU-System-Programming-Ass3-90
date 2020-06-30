package bgu.spl.net.impl.Frames.ServerToClient;

public class ErrorFrame {
    String errorMsg;
    String msg;

    public ErrorFrame(String errorMsg) {
        this.errorMsg = errorMsg;

    }

    public String getErrorMsg(){
        this.msg = "ERROR\nmessage: "+errorMsg+"\n\n^@";
//        System.out.println(msg);
        return msg;
    }
}
