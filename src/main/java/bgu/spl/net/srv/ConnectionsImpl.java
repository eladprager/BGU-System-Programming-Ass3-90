package bgu.spl.net.srv;

import bgu.spl.net.Pair;
import bgu.spl.net.impl.rci.RCIClient;
//import jdk.internal.net.http.common.Pair;
//import com.sun.jdi.connect.spi.Connection;
//import com.sun.security.ntlm.Client;

import java.io.IOException;
import java.nio.channels.Channel;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class ConnectionsImpl<T> implements Connections<T> {

    AtomicInteger num = new AtomicInteger(0);
    private ConcurrentHashMap<Integer,ConnectionHandler> clientConnectionHandlerMap = new ConcurrentHashMap<>(); // userId, ConnectionHandler
    private ConcurrentHashMap<String,LinkedList<ConnectionHandler>> ChannelClientMap = new ConcurrentHashMap<>(); //Channel, Users
    private ConcurrentHashMap<Pair<String,String>,Integer> subIdMap = new ConcurrentHashMap<>(); // Pair<username,genre>,subId
    private ConcurrentHashMap<Integer,String> IdUserMap = new ConcurrentHashMap<>();
//    private ConcurrentHashMap<String,String> UserBorrowBook = new ConcurrentHashMap<>();


    @Override
    public boolean send(int connectionId, T msg) { // send to given user
        ConnectionHandler hand = clientConnectionHandlerMap.get(connectionId);
        synchronized (hand) {
            if (!clientConnectionHandlerMap.containsKey(connectionId)) return false;
            else {
                clientConnectionHandlerMap.get(connectionId).send(msg);
            }
            return true;
        }
    }

//    public void addToBorrowBookMap(String Book,String Name){
//        this.UserBorrowBook.put(Book,Name);
//    }
//
//    public void delFromBorrowBookMap(String Book,String Name){
//        this.UserBorrowBook.remove(Book,Name);
//    }
//
//    public String getNameByBook(String book){
//        return this.UserBorrowBook.get(book);
//    }

    @Override
    public void send(String channel, T msg) { // send to channel;
        for (int i = 0;!ChannelClientMap.isEmpty()&&!ChannelClientMap.get(channel).isEmpty()&&i < ChannelClientMap.get(channel).size(); i++) {
            synchronized (ChannelClientMap.get(channel).get(i)) {
                ChannelClientMap.get(channel).get(i).send(msg);
            }
        }
    }

    @Override
    public void disconnect(int connectionId) {
        synchronized (this.clientConnectionHandlerMap.get(connectionId)) {
            clientConnectionHandlerMap.remove(connectionId);
        }
    }

    public boolean isConnected(int connectionId){
        if (clientConnectionHandlerMap.containsKey(connectionId)){
            return true;
        }
        return false;
    }

    void deleteFromClientConnectionHandler(ConnectionHandler c){
        for (Map.Entry<Integer,ConnectionHandler> entry : this.clientConnectionHandlerMap.entrySet()){
            if (entry.getValue().equals(c)){
                this.clientConnectionHandlerMap.remove(entry.getKey());
            }
        }
    }

    void deleteFromChannelMap(ConnectionHandler c){
        for (Map.Entry<String,LinkedList<ConnectionHandler>> entry : this.ChannelClientMap.entrySet()){
            if (entry.getValue().contains(c)){
                entry.getValue().remove(c);
            }
        }
    }

    String deleteFromIdUserMapById(int connectionId){
        String toReturn = this.IdUserMap.get(connectionId);
        this.IdUserMap.remove(connectionId);
        return toReturn;
    }

    void deleteFromSubIdMapByUserName(String username){
        for (Map.Entry<Pair<String,String>,Integer> entry : this.subIdMap.entrySet()){
            if (entry.getKey().first().equals(username)){
                this.subIdMap.remove(entry.getKey());
            }
        }
    }

    public ConnectionHandler getConnectionHandler(int connectionId) {
        return clientConnectionHandlerMap.get(connectionId);
    }

    public void subscribe(String username,String genre,int subId,int connectionId){
        ConnectionHandler c = this.clientConnectionHandlerMap.get(connectionId);
        if (!this.ChannelClientMap.containsKey(genre)){
            LinkedList<ConnectionHandler> l = new LinkedList<>();
            l.add(c);
            this.ChannelClientMap.put(genre,l);
        }
        else {
            this.ChannelClientMap.get(genre).add(c);
        }
        Pair newpair = new Pair(username,genre);
        subIdMap.put(newpair,subId);
    }

    public void unsubscribe(String username,String genre,int connectionId){
        ConnectionHandler c = this.clientConnectionHandlerMap.get(connectionId);
        for (int i = 0; i < this.ChannelClientMap.get(genre).size(); i++){
            if (this.ChannelClientMap.get(genre).get(i).equals(c)){
                this.ChannelClientMap.get(genre).remove(i);
            }
        }
        Pair<String,String> toDelete = new Pair(username,genre);
        for (Map.Entry<Pair<String,String>,Integer> entry : this.subIdMap.entrySet()){
            if (entry.getKey().equals(toDelete)){
                this.subIdMap.remove(entry.getKey());
            }
        }
    }

    public String getGenreBySubId(int sub){
        for (Map.Entry<Pair<String,String>,Integer> entry : subIdMap.entrySet()){
            if (sub == entry.getValue()) return entry.getKey().second();
        }
        return "";
    }

    public int getSubIDbyGenreUser(String user,String genre){
        Pair<String,String> p = new Pair(user,genre);
        for (Map.Entry<Pair<String,String>,Integer> entry : this.subIdMap.entrySet()){
            if (entry.getKey().equals(p)){
                return this.subIdMap.get(entry.getKey());
            }
        }
        return -1;
    }

    public void addUserid (String user,int id){
        IdUserMap.put(id,user);
    }

     public String getUserById(int id){
        return IdUserMap.get(id);
     }

     public int addclientConnectionHandler(ConnectionHandler f){
         clientConnectionHandlerMap.put(this.num.getAndIncrement(),f);
         return this.num.get()-1;
     }

    public void disconnectAll() {
        for (ConnectionHandler<T> toClose : clientConnectionHandlerMap.values())
            try {
                toClose.close();
            }
            catch (IOException ignored) {
            }
        clientConnectionHandlerMap.clear();
    }
}
