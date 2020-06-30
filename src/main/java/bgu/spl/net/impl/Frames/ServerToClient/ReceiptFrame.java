package bgu.spl.net.impl.Frames.ServerToClient;

public class ReceiptFrame {

    String msg;
    int id;

    public ReceiptFrame(int id) {
        this.id =id;
    }

    public String send() {
        msg = "RECEIPT\nreceipt-id:"+id+"\n\n^@";
//        System.out.println(msg);
        return msg;
    }
}
