package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.BookClub;
import bgu.spl.net.impl.stomp.Frames.*;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

public class StompProtocol implements StompMessagingProtocol<Frame> {

    private int connectionId;
    private volatile boolean shouldTerminate;
    private String userName;

    private ConnectionsImpl<Frame> connections;
    private final BookClub bookClub;

    public StompProtocol(BookClub bookClub) {

        this.connectionId = -1;
        this.shouldTerminate = false;
        this.userName = "";//either it is a " " or the name of the the current connected user
        this.connections = null;
        this.bookClub = bookClub;

    }

    public ConnectionsImpl<Frame> getConnections() {
        return connections;
    }

    @Override
    public void start(int connectionId, Connections<Frame> connections) {
        this.connections = (ConnectionsImpl<Frame>)connections;
        this.connectionId = connectionId;
    }

    @Override
    public void process(Frame frame) {
        frame.process(this);
    }

    @Override
    public boolean shouldTerminate() {
        return false;
    }

    public BookClub getBookClub() {
        return this.bookClub;
    }

    public String getOnLineUserName() {
        return this.userName;
    }

    public int getConnectionId() {
        return this.connectionId;
    }
}
