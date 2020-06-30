package bgu.spl.net.srv;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.Frames.ServerToClient.ConnectedFrame;
import bgu.spl.net.impl.Frames.ServerToClient.ErrorFrame;
import bgu.spl.net.impl.Frames.ServerToClient.MessageFrame;
import bgu.spl.net.impl.Frames.ServerToClient.ReceiptFrame;

import java.util.concurrent.atomic.AtomicInteger;

public class StompMessagingProtocolImpl implements StompMessagingProtocol<String> {

    private int connectionId;
    private ConnectionsImpl<String> connections;
    private boolean shouldTerminate = false;
    private AtomicInteger messageId=new AtomicInteger(0);
    private int receiptId;
//    private int newuserid;

    @Override
    public void start(int connectionId, ConnectionsImpl<String> connections) {
        this.connectionId=connectionId;
        this.connections=connections;
//        this.newuserid=0;

    }

    @Override
    public void process(String message) {
        System.out.println(message+"\n");
//        List<String> list=new ArrayList<>();
//        Matcher m= Pattern.compile("([^\"]\\S*|\".+?\")\\s*").matcher(message);
//        while (m.find())
//            list.add(m.group(1).replace("\"", ""));
//        String[] msg=new String[list.size()];
//        list.toArray(msg);
        String [] msg = message.split("\n");
        if (msg.length==0)
        {
            connections.send(connectionId, "ERROR request is empty!!");
            return;
        }
        switch (msg[0])
        {
            case "CONNECT":
                connect(msg);
                break;
            case "SUBSCRIBE":
                subscribe(msg);
                break;
            case "UNSUBSCRIBE":
                unsubscribe(msg);
                break;
            case "SEND":
                send(msg);
                break;
            case "DISCONNECT":
                disconnect(this.connections.getConnectionHandler(this.connectionId));
                break;
            default:
                connections.send(connectionId, "ERROR request type "+msg[0]+" not legal!!");
        }

    }



    private void send(String[] msg) {
        if (msg[3].contains("added")) {
            String name=msg[3].split(" ")[0];
            String genre=msg[1].split(":")[1];
            String bookName=msg[3].split(" ")[5];
            for (int i = 6; i < msg[3].split(" ").length; i++){
                bookName=bookName+" "+ msg[3].split(" ")[i];
            }
            for (int i=0;i < Users.getAllUsers().size(); i++){
                if (Users.getAllUsers().get(i).getUsername().equals(name)){
                    Book newBook = new Book(bookName,genre);
//                    newBook.setOwner(Users.getAllUsers().get(i));
                    Users.getAllUsers().get(i).addUserBook(newBook);
                }
            }
            MessageFrame add = new MessageFrame(msg, this.connections.getSubIDbyGenreUser(name,genre), messageId.getAndIncrement());
            connections.send(genre, add.send());
        }
        if (msg[3].contains("borrow")){
            String [] tmp = msg[3].split(" ");
            String genre=msg[1].split(":")[1];
            String userName=tmp[0];
            String bookName = tmp[4];
            for (int i = 5; i < tmp.length; i++){
                bookName=bookName+" "+tmp[i];
            }
            MessageFrame add = new MessageFrame(msg, this.connections.getSubIDbyGenreUser(userName,genre), messageId.getAndIncrement());
            connections.send(genre, add.send());


//            this.connections.addToBorrowBookMap(bookName,userName);
            Users.User tmpuser=Users.getUserByName(userName);
            for (int i=0;i<Users.getAllUsers().size();i++){
                for (int j=0;j<Users.getAllUsers().get(i).getBooks().size();j++){
                    if (Users.getAllUsers().get(i).getBooks().get(j).getBookName().equals(bookName)){
                        Book tmpbook=Users.getAllUsers().get(i).getBooks().get(j);
                        tmpuser.getBook(tmpbook);
                        tmpbook.addToBookHistory(tmpuser);
                        break;
                    }
                }
            }
//            MessageFrame borrow = new MessageFrame(msg,this.connections.getSubIDbyGenreUser(userName,genre),messageId,"borrow_1");
//            connections.send(genre, borrow.send());
//            messageId++;
//            MessageFrame borrow_2 = new MessageFrame(msg,this.connections.getSubIDbyGenreUser(userName,genre),messageId,"borrow_2");
//            connections.send(genre, borrow_2.send());
//            messageId++;
        }


        if (msg[3].contains("has") && !msg[3].contains("added")) {
            String genre=msg[1].split(":")[1];
            String user = this.connections.getUserById(this.connectionId);
            MessageFrame has = new MessageFrame(msg,this.connections.getSubIDbyGenreUser(user,genre), messageId.getAndIncrement());
            connections.send(genre, has.send());
        }




        if (msg[3].contains("Taking")){
            String genre=msg[1].split(":")[1];
//            String [] tmp = msg[3].split(" ");
//            String book = tmp[1];
//            int j=0;
//            for (int i = 0; i < tmp.length; i++){
//                if (tmp[i] == "from"){
//                    j=i;
//                    break;
//                }
//            }
//            for (int i = 2; i < j; i++){
//                book=book+" "+tmp[i];
//            }
//            String user = this.connections.getNameByBook(book);
            String user = this.connections.getUserById(this.connectionId);
            MessageFrame borrow_3 = new MessageFrame(msg,this.connections.getSubIDbyGenreUser(user,genre),messageId.getAndIncrement());
//            this.connections.delFromBorrowBookMap(book,user);
            connections.send(genre, borrow_3.send());
        }
        if (msg[3].contains("Returning")){
            String genre=msg[1].split(":")[1];
            int j = 0;
            for (int i = 0; i < msg[3].split(" ").length; i++){
                if (msg[3].split(" ")[i].equals("to")){
                    j=i;
                }
            }
            String bookName=msg[3].split(" ")[1];
            for (int i = 0; i < j; i++){
                bookName=bookName+" "+msg[3].split(" ")[i];
            }
            for (int i=0;i<Users.getAllUsers().size();i++){
                for (int k=0;k<Users.getAllUsers().get(i).getBooks().size();k++){
                    if (Users.getAllUsers().get(i).getBooks().get(k).getBookName().equals(bookName)){
                        Book tmpBook=Users.getAllUsers().get(i).getBooks().get(k);
                        tmpBook.returnBook();
                    }
                }
            }
            String user = this.connections.getUserById(this.connectionId);
            MessageFrame Return = new MessageFrame(msg,this.connections.getSubIDbyGenreUser(user,genre),messageId.getAndIncrement());
            connections.send(genre, Return.send());
        }
        if (msg[3].contains("status")) {
            String genre=msg[1].split(":")[1];
            String user = this.connections.getUserById(this.connectionId);
            MessageFrame status = new MessageFrame(msg,this.connections.getSubIDbyGenreUser(user,genre), messageId.getAndIncrement());
            connections.send(genre, status.send());
        }
        if (msg[3].contains(":")) {
            String genre=msg[1].split(":")[1];
            String user = this.connections.getUserById(this.connectionId);
            MessageFrame status_2 = new MessageFrame(msg, this.connections.getSubIDbyGenreUser(user,genre), messageId.getAndIncrement());
            connections.send(genre, status_2.send());
        }
//        else {
//                connections.send(connectionId, "ERROR request " + msg[1] + " not legal!!");
//                messageId++;
//            }
        }




    private void connect(String[] msg) {
        if (!connections.isConnected(connectionId)) {
            connections.send(connectionId, "Could not connect to server");
        } else {
            if (connections.getConnectionHandler(connectionId) instanceof NonBlockingConnectionHandler) {
                if (((NonBlockingConnectionHandler) connections.getConnectionHandler(connectionId)).isLoggedIn()) {
                    ErrorFrame error = new ErrorFrame("User already logged in");
                    connections.send(connectionId, error.getErrorMsg());
                } else {
                    String name = msg[3].split(":")[1];
                    String password = msg[4].split(":")[1];
                    boolean contains = false;
                    for (Users.User user : Users.getAllUsers()) {
                        if (name.equals(user.getUsername())) {
                            contains = true;
                            if (user.getPassword().equals(password)) {
                                ConnectedFrame connected = new ConnectedFrame(1.2);
                                connections.send(connectionId, connected.send());
                            } else {
                                ErrorFrame error = new ErrorFrame("Wrong password");
                                connections.send(connectionId, error.getErrorMsg());
                            }
                            break;
                        }
                    }
                    if (!contains) {
                        Users.addUser(new Users.User(name, password));
                        ConnectedFrame connected = new ConnectedFrame(1.2);
                        connections.send(connectionId, connected.send());
                        connections.addUserid(name,this.connectionId);
                    }
                }
            } else if (connections.getConnectionHandler(connectionId) instanceof BlockingConnectionHandler) {
                if (((BlockingConnectionHandler) connections.getConnectionHandler(connectionId)).isLoggedIn()) {
                    ErrorFrame error = new ErrorFrame("User already logged in");
                    connections.send(connectionId, error.getErrorMsg());
                } else {
                    String name = msg[3].split(":")[1];
                    String password = msg[4].split(":")[1];
                    boolean contains = false;
                    for (Users.User user : Users.getAllUsers()) {
                        if (name.equals(user.getUsername())) {
                            contains = true;
                            if (user.getPassword().equals(password)) {
                                ConnectedFrame connected = new ConnectedFrame(1.2);
                                connections.send(connectionId, connected.send());
                            } else {
                                ErrorFrame error = new ErrorFrame("Wrong password");
                                connections.send(connectionId, error.getErrorMsg());
                            }
                            break;
                        }
                    }
                    if (!contains) {
                        Users.addUser(new Users.User(name, password));
                        ConnectedFrame connected = new ConnectedFrame(1.2);
                        connections.send(connectionId, connected.send());
                        connections.addUserid(name,this.connectionId);
                    }
                }
            }
        }
    }

    private void subscribe(String[] msg) {
        String genre = msg[1].split(":")[1];
        String username = connections.getUserById(this.connectionId);
        int subID=0;
        if (connections.getConnectionHandler(connectionId) instanceof NonBlockingConnectionHandler) {
            subID = ((NonBlockingConnectionHandler) connections.getConnectionHandler(this.connectionId)).getSubID();
        } else if (connections.getConnectionHandler(connectionId) instanceof BlockingConnectionHandler) {
            subID = ((BlockingConnectionHandler) connections.getConnectionHandler(this.connectionId)).getSubID();
        }
        ReceiptFrame receipt = new ReceiptFrame(receiptId);
        connections.send(this.connectionId, receipt.send());
        connections.subscribe(username, genre,subID,this.connectionId);
        receiptId++;
        }

    private void unsubscribe(String[] msg) {
        ReceiptFrame receipt = new ReceiptFrame(receiptId);
        int subID = Integer.parseInt(msg[1].split(":")[1]);
        String genre = this.connections.getGenreBySubId(subID);
        String name = connections.getUserById(connectionId);
        connections.send(this.connectionId, receipt.send());
        connections.unsubscribe(name,genre,connectionId);
        receiptId++;
    }

    private void disconnect(ConnectionHandler c){
        ReceiptFrame receipt = new ReceiptFrame(receiptId);
        connections.send(connectionId, receipt.send());
        this.connections.deleteFromClientConnectionHandler(c);
        this.connections.deleteFromChannelMap(c);
        String user = this.connections.deleteFromIdUserMapById(this.connectionId);
        this.connections.deleteFromSubIdMapByUserName(user);
        this.shouldTerminate=true;
        receiptId++;
    }

    @Override
    public boolean shouldTerminate() {
        return this.shouldTerminate;
    }
}
