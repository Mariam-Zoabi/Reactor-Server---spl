package bgu.spl.net.srv;


import java.io.IOException;
import java.util.LinkedList;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import java.util.concurrent.atomic.AtomicInteger;

public class ConnectionsImpl<T> implements Connections<T> {

    private final Map<Integer, ConnectionHandler<T>> mClientConnection;// Key: Client's ID, value: client's ConnectionHandler
    private final Map<String, Map<Integer, String>> mClientsSubToTopic;//Key - topic name *** Value-(Key- connectionId. ** Value -topic id of user)
    private final AtomicInteger idCounter;
    private final Object lock;
    private final Object lock2;

    public ConnectionsImpl() {
        this.mClientConnection = new ConcurrentHashMap<>();
        this.mClientsSubToTopic = new ConcurrentHashMap<>();
        this.idCounter = new AtomicInteger(); // default value 0.
        this.lock = new Object();
        this.lock2 = new Object();
    }

    /**
     * Add the new handler to the connection collection.
     *
     * @param handler The connectionHandler to be added.
     * @return the connectionId that the handler got.
     */

    public int add(ConnectionHandler<T> handler) {
        int id = this.idCounter.getAndIncrement();
        this.mClientConnection.put(id, handler);
        return id;
    }

    public void register(String topic, int connectionID,String str_Id) {
        this.mClientsSubToTopic.putIfAbsent(topic,new ConcurrentHashMap<>());
        this.mClientsSubToTopic.get(topic).putIfAbsent(connectionID,str_Id);
        for(Map.Entry<String,Map<Integer,String>> entery :this.mClientsSubToTopic.entrySet())
        {
            String out1 = entery.getKey();
            for(Map.Entry<Integer,String> entery2: this.mClientsSubToTopic.get(out1).entrySet())
            {
                Integer out2 = entery2.getKey();
                String out3 = entery2.getValue();
                System.out.println(out1);
                System.out.println(out2);
                System.out.println(out3);
            }
        }
    }

    public void unregisterFromAllTopics(int id){
        for(Map.Entry<String,Map<Integer,String>> entry: this.mClientsSubToTopic.entrySet())
        {
            String topic = entry.getKey();
            synchronized (this.mClientsSubToTopic.get(topic)) {
                if (this.mClientsSubToTopic.containsKey(topic))
                    this.mClientsSubToTopic.get(topic).remove(id);
                if(mClientsSubToTopic.get(topic).isEmpty())
                    this.mClientsSubToTopic.remove(topic);


            }
        }

    }

    public void unregister(String topic , int id){
        synchronized (lock2) {
            if (this.mClientsSubToTopic.containsKey(topic))
                this.mClientsSubToTopic.get(topic).remove(id);
            if(mClientsSubToTopic.get(topic).isEmpty()){
                this.mClientsSubToTopic.remove(topic);

            }
        }
    }


    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler<T> handler = this.mClientConnection.get(connectionId);
        if (handler == null)
            return false;
        synchronized (handler) {
            handler.send(msg);
        }
        return true;
    }

    @Override
    public void send(String channel, T msg) {
        Map<Integer,String> sendToSub = mClientsSubToTopic.get(channel);
        if (sendToSub == null)
            return;
        for (Integer id : mClientsSubToTopic.get(channel).keySet()) {
            send(id, msg);
        }
    }

    @Override
    public LinkedList<String> disconnect(int connectionId) {

        LinkedList<String> topics2Remove = new LinkedList<>();
        ConnectionHandler<T> handler = this.mClientConnection.remove(connectionId);
        try {
            if (handler != null) {
                synchronized (handler) {
                    handler.close();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        synchronized (lock) {
            for (String topic : this.mClientsSubToTopic.keySet()) {
                Map<Integer, String> subToMap = this.mClientsSubToTopic.get(topic);
                subToMap.remove(connectionId);
                if(subToMap.isEmpty()) {
                    topics2Remove.add(topic);
                    this.mClientsSubToTopic.remove(topic);

                }
                //https://www.cs.bgu.ac.il/~spl201/index.php?page=Assignments.Assignment_3&action=show-thread&id=8d1092b5ec0cfd4c8b8836027146acca
            }
        }
        return topics2Remove;
    }

    public Map<String, Map<Integer,String>> getMClientTotopic(){
        return this.mClientsSubToTopic;
    }

    public String getByValueOfTopicId(int connectionId, String str_id) {

        for(Map.Entry<String,Map<Integer,String>> entery: mClientsSubToTopic.entrySet()){
            String topic = entery.getKey();
            for(Map.Entry<Integer,String> entery2: mClientsSubToTopic.get(topic).entrySet())
            {

                int id = entery2.getKey();
                String topicid = entery2.getValue();

                if(id==connectionId&&str_id.equals(topicid))
                    return entery.getKey();
            }


        }
        return null;
    }
}
