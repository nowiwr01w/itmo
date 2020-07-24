package ru.ifmo.rain.larionov.hello;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

class Util {

    static DatagramPacket receivePacket(final DatagramSocket socket, final int bufferSize) throws IOException {
        final var packet = new DatagramPacket(ByteBuffer.allocate(bufferSize).array(), bufferSize);
        socket.receive(packet);
        return packet;
    }

    static String getMessage(final DatagramPacket packet) {
        return new String(packet.getData(), packet.getOffset(), packet.getLength(), StandardCharsets.UTF_8);
    }

    static void handleIOException(final IOException ex) {
        System.err.println("I/O error at hello:");
        System.err.println(ex.getMessage());
    }
}
