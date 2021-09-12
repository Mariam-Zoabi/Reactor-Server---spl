package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.BookClub;
import bgu.spl.net.impl.stomp.StompProtocol;
import bgu.spl.net.srv.ConnectionsImpl;

public class UNSUBSCRIBE extends Frames2Get{
    @Override
    public void process(StompProtocol protocol) {
        ConnectionsImpl connections = protocol.getConnections();
        String str_id = get("id");
        String receipt = get("receipt");
        BookClub bookClub = protocol.getBookClub();
        String topicName = connections.getByValueOfTopicId(protocol.getConnectionId(),str_id);

        connections.unregister(topicName , protocol.getConnectionId());
        RECEIPT result = new RECEIPT();
        result.put("receipt-id",receipt);
        connections.send(protocol.getConnectionId(),result);

    }
}
