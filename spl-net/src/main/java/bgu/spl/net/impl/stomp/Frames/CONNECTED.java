package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.stomp.StompProtocol;

public class CONNECTED extends Frames2Give {
    @Override
    public void process(StompProtocol protocol) {
        System.out.print("Im in CONNCTED process");
        return;
    }
}
