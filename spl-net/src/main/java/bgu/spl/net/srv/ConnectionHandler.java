/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bgu.spl.net.srv;

import java.io.Closeable;

/**
 * The ConnectionHandler interface for Message of type T
 */
public interface ConnectionHandler<T> extends Closeable {

    /**
     * Sends message to the client.
     * Should be used by {@link Connections#send(int, Object)} and {@link Connections#send(String, Object)}
     * in the {@link Connections} implementation.
     * @param msg Message to be sent.
     */

    void send(T msg);

}
