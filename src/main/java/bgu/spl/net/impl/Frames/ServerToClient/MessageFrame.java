package bgu.spl.net.impl.Frames.ServerToClient;

public class MessageFrame {

    private String destination;
    public String[] message;
    private String msg;
    private int subId;
    private int messageId;

    public MessageFrame(String [] input, int subId, int messageId) {
        this.message = input;
        this.destination = input[1].split(":")[1];
        this.subId = subId;
        this.messageId = messageId;
    }


    public String send() {
        msg = "MESSAGE\nsubscription:"+subId+"\nMessage-id:"+messageId+"\ndestination:"+destination+"\n\n"+message[3]+"\n^@";
//        System.out.println(msg);
        return (msg);
//        switch (command) {
//            case "add":
//            case "borrow_1":
//            case "borrow_3":
//            case "return":
//            case "status_1":
//            case "status_2":
//                msg=msg+message[3]+"\n^@";
//                System.out.println(msg);
//                return (msg);
//            case "borrow_2":
//                this.name = message[3].split(" ")[0];
//                this.second_name = message[3].split(" ")[4];
//                msg=msg+name+" has "+second_name+"\n^@";
//                System.out.println(msg);
//                return (msg);
//            default:
//                System.out.println(msg);
//                return (msg);

    }
}
