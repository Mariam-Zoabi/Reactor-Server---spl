package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.impl.stomp.StompProtocol;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;

public class MESSAGE extends Frames2Give {
     AtomicInteger messagesCounter = new AtomicInteger();

     public MESSAGE(){
         this.messagesCounter.incrementAndGet();

     }


    @Override
    public void process(StompProtocol protocol) {
        System.out.print("Im in MSG process");
         return;
    }

    public AtomicInteger getMsgID(){
         return this.messagesCounter;
    }
}
