package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.stomp.StompProtocol;

public class ERROR extends Frames2Give {

    private String returnFrame;

    public ERROR(String theErrorType){
        if(theErrorType.equals("login")){
            returnFrame = "ERROR\n" + "User already logged in";
        }
        if(theErrorType.equals("psw"))
        {
            returnFrame = "ERROR\n" + "Wrong password";
        }
       // if(theErrorType.equals(""))
    }

    @Override
    public void process(StompProtocol protocol) {

    }
}
