package bgu.spl.net.impl;


import bgu.spl.net.impl.stomp.Frames.Frame;

import java.util.Map;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;


public class BookClub {
    private final Map<String, User> theUsersHolder;
    private Map<String , String> topicToIdMap;
    private  Map<String ,Integer> onlineUsers;


    public BookClub() {
        this.theUsersHolder = new ConcurrentHashMap<>();
      //  this.topicToMessages = new ConcurrentHashMap<>();
        this.onlineUsers = new ConcurrentHashMap<>();
       this.topicToIdMap = new ConcurrentHashMap<>();
    }


    public boolean addIfAbsent(String name, String pass) {
        return theUsersHolder.putIfAbsent(name, new User(name, pass)) == null;

    }

    public User getUserByName(String name) {
        return theUsersHolder.get(name);
    }




    public boolean addActiveUser(String name, Integer connectionID){
        return this.onlineUsers.putIfAbsent(name,connectionID) == null;
    }

    public void removeOnlineUser(String name) {
        this.onlineUsers.remove(name);
    }

    public Map<String,Integer> getAllOnlineUsers() {
        return onlineUsers;
    }

    public void addTopic2Id(String topic , String id){
        this.topicToIdMap.putIfAbsent(topic , id);
    }

    public void deleteTopicId(String topic){
        this.topicToIdMap.remove(topic);
    }


    public String getTopicID(String topic)
    {
        return this.topicToIdMap.get(topic);
    }

    public String getByValueOfTopicId(String str_id){
        String topicName = null;
        for(Map.Entry<String , String> topic : this.topicToIdMap.entrySet()){
            String v = topic.getValue();
            if(v.equals(str_id))
                topicName = topic.getKey();
        }
        return topicName;
    }
}
