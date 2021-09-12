package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.BookClub;
import bgu.spl.net.impl.stomp.StompProtocol;
import bgu.spl.net.srv.ConnectionsImpl;

public class SUBSCRIBE extends Frames2Get {
    @Override
    public void process(StompProtocol protocol) {
        ConnectionsImpl connections = protocol.getConnections();
        BookClub bookClub = protocol.getBookClub();
        String destination = get("destination");
        String str_id = get("id");
        bookClub.addTopic2Id(destination , str_id);
        String receipt = get("receipt");

        RECEIPT result = new RECEIPT();

        connections.register(destination , protocol.getConnectionId(), str_id);
        result.put("receipt-id",receipt);
        connections.send(protocol.getConnectionId(),result);
    }
}
