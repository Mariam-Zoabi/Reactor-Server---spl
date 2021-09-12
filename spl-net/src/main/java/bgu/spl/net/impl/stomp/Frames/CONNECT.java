package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.BookClub;
import bgu.spl.net.impl.User;
import bgu.spl.net.impl.stomp.StompProtocol;
import bgu.spl.net.srv.Connections;

public class CONNECT extends Frames2Get {

    @Override
    public void process(StompProtocol protocol) {
        BookClub bookClub = protocol.getBookClub();
        Connections<Frame> connections = protocol.getConnections();


        String username = get("login");
        String password = get("passcode");
        bookClub.addIfAbsent(username, password);

        User user = bookClub.getUserByName(username);

        if (!user.password.equals(password)) {
                        connections.send(protocol.getConnectionId(), new ERROR("psw"));
            return;
        }

        if(!bookClub.addActiveUser(username,protocol.getConnectionId())) {
            if (!user.try2login(protocol.getConnectionId())) {
                connections.send(protocol.getConnectionId(), new ERROR("login"));
                return;
            }
        }
      //  bookClub.addActiveUser(username);

        CONNECTED connected = new CONNECTED();
        connected.put("version", this.get("accept-version"));
        connections.send(protocol.getConnectionId(), connected);
        }
    }
