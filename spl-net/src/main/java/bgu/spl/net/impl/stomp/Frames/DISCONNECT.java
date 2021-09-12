package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.BookClub;
import bgu.spl.net.impl.stomp.StompProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

import java.util.LinkedList;

public class DISCONNECT extends Frames2Get {
    @Override
    public void process(StompProtocol protocol) {
        System.out.println("I got here");
        BookClub bookClub = protocol.getBookClub();
        ConnectionsImpl<Frame> connections = protocol.getConnections();
        String receipt = get("receipt");

        RECEIPT result = new RECEIPT();
        int connectionId = protocol.getConnectionId();



        bookClub.removeOnlineUser(protocol.getOnLineUserName());
        result.put("receipt-id", receipt);
        connections.send(protocol.getConnectionId(), result);


        connections.unregisterFromAllTopics(connectionId);


    }
}
