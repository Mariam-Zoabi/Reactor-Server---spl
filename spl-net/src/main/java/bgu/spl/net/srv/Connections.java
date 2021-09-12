package bgu.spl.net.srv;

import java.io.IOException;
import java.util.LinkedList;

public interface Connections<T> {

    int add(ConnectionHandler<T> handler);//add handler, return its id

    void register(String topic, int connectionID, String str_Id);

    boolean send(int connectionId, T msg);

    void send(String channel, T msg);

    LinkedList<String> disconnect(int connectionId);

}
