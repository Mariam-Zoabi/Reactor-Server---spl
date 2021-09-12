package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.impl.stomp.Frames.Frame;

import java.lang.reflect.Constructor;
import java.nio.charset.StandardCharsets;
import java.util.LinkedList;
import java.util.Map;

public class StompEncoderDecoder implements MessageEncoderDecoder<Frame> {

    private LinkedList<Byte> bytes = new LinkedList<>();
    private int i = 0;

    @Override
    public Frame decodeNextByte(byte nextByte) {
        if (nextByte == '\0') {
            return popString();
        }

        pushByte(nextByte);

        return null;
    }


    private void pushByte(byte nextByte) {
        bytes.add(nextByte);
    }

    @SuppressWarnings("unchecked")
    private Frame popString() {
        String msgAsString = convertList2Str();
        Frame frame;
        try {

            String typeName = msgAsString.split("\n")[0];

            Class<Frame> type = (Class<Frame>) Class.forName("bgu.spl.net.impl.stomp.Frames."+typeName);
            Constructor<Frame> constructor = type.getConstructor();
            frame = constructor.newInstance();

            msgAsString = msgAsString.substring(typeName.length() + 1);
            msgAsString = msgAsString.replaceFirst("\n\n", "\nbody:");

            String[] lines = msgAsString.split("\n");
            for (String line : lines) {
                String[] kv = line.split(":",2);

                frame.put(kv[0], kv[1]);
            }

        } catch (Exception e) {
            frame = null;
        }
        return frame;
    }

    private String convertList2Str() {
        byte[] arr = new byte[bytes.size()];
        bytes.forEach(b -> arr[i++] = b);
        i = 0;
        bytes.clear();
        String x = new String(arr, StandardCharsets.UTF_8);
        return x;
    }


    @Override
    public byte[] encode(Frame message) {
        String string = "";

        string = message.getClass().getSimpleName() + "\n";

        Map<String, String> headers = message.getHeaders();

        for (Map.Entry<String, String> entry : headers.entrySet()) {
            String k = entry.getKey();
            String v = entry.getValue();

            string += k + ":" + v + "\n";
        }
        string=string.replace("body:","\n");
        string = string.substring(0,string.length()-1);
        System.out.println(string);
        return (string + "\0").getBytes();
    }

}
