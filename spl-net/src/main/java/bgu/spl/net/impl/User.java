package bgu.spl.net.impl;

import java.util.LinkedList;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class User {

    public final String name;
    public final String password;
    private AtomicInteger connectionID;
    private volatile boolean isOnline;
    //private int receiptID;
    private Map<Integer , Boolean> receiptIdOnLineNotOnLine;
   // private LinkedList<String> topicsList;



    public User(String name, String password) {
        this.name = name;
        this.password = password;
        this.connectionID = new AtomicInteger(-1);
        //this.isOnline = false;
        // this.receiptID = -1;
    }

    /*public LinkedList<String> getTopicsList(){
        return this.topicsList;
    }*/

    /*public void addToTopicList(String genere) {
        this.topicsList.add(genere);
    }*/

    public String getPassword() {
        return this.password;
    }

    public boolean try2login(int connectionId) {
        return connectionID.compareAndSet(-1, connectionId);
    }

    public void setConnectionID(int i){
            this.connectionID.getAndSet(i);
    }

    public int getUserID() {
        return this.connectionID.get();
    }


}
