package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.BookClub;
import bgu.spl.net.impl.stomp.StompProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

import java.util.Map;

public class SEND extends Frames2Get {
    @Override
    public void process(StompProtocol protocol) {
        BookClub bookClub = protocol.getBookClub();
        ConnectionsImpl<Frame> connections = protocol.getConnections();
        MESSAGE msg = new MESSAGE();
        String body = get("body");
        String topic = get("destination");
        String[] theFirstWord = body.split( " ", 2);
        msg.put("subscription", bookClub.getTopicID(topic));
        msg.put("Message-id",msg.getMsgID().toString());
        msg.put("destination",topic);
        msg.put("","\n"+body);
        connections.send(topic, msg);


    }
/*
    private String [] splitForSend(String key, String body, BookClub bookClub)
    {
        for (Map.Entry<String, Boolean> entry : bookClub.getAllOnlineUsers().entrySet()) {
            String[] res = new String[2]; //0 = book name. 1 = user to return name
            String[] temp = body.split( " to ", 2);
            temp[0].replaceFirst(key+" ", "");
            res[0] = temp[0];
            String name = entry.getKey();
            boolean isDone = false;
            while(!isDone) {
                if (temp[1].equals(name)) {
                    res[1] = temp[1];
                    return res;
                }
                if(temp[1].contains(" to ")) {
                    temp = temp[1].split(" to ", 2);
                    res[0] = res[0] + " to " + temp[0];
                }
                else
                    isDone = true;
            }
        }
        return null;
    }

 */
}
