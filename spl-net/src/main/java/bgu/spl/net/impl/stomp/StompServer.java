package bgu.spl.net.impl.stomp;

import bgu.spl.net.impl.BookClub;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {
        int port = Integer.parseInt(args[0]);
            if(args[1].equals("tpc"))
                     runThreadPerClient(port);
            else
                runReactor(port);


    }

    private static void  runThreadPerClient(int port){
        BookClub bookClub = new BookClub();//the shared object
        Server.threadPerClient(port, () -> new StompProtocol(bookClub), StompEncoderDecoder::new).serve();
    }

    private static void runReactor(int port){
        BookClub bookClub = new BookClub();
        Server.reactor(Runtime.getRuntime().availableProcessors(),port,
                () -> new StompProtocol(bookClub),
                StompEncoderDecoder::new).serve();
    }
}
