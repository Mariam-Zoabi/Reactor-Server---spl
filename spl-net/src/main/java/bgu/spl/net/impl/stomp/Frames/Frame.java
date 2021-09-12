package bgu.spl.net.impl.stomp.Frames;

import bgu.spl.net.impl.stomp.StompProtocol;

import java.util.LinkedHashMap;
import java.util.Map;

public abstract class Frame {
    private Map<String, String> headers = new LinkedHashMap<>();

    public void put(String s, String s2) {
        headers.put(s, s2);
    }

    public String get(String s) {
        return headers.get(s);
    }

    public Map<String, String> getHeaders() {
        return headers;
    }

    public abstract void process(StompProtocol protocol);
}
