package ru.ifmo.rain.larionov.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.io.IOException;
import java.net.DatagramSocket;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.*;

import static ru.ifmo.rain.larionov.hello.Util.handleIOException;

public class HelloUDPServer implements HelloServer {

    private static final int QUEUE_SIZE = 1 << 16;

    private DatagramSocket socket = null;
    private ExecutorService executor = null;
    private ExecutorService connectionsHandler = null;

    @Override
    public void start(final int port, final int threads) {
        close();
        try {
            connectionsHandler = Executors.newSingleThreadExecutor();
            executor = new ThreadPoolExecutor(threads, threads, 30, TimeUnit.SECONDS,
                    new ArrayBlockingQueue<>(QUEUE_SIZE), new ThreadPoolExecutor.DiscardPolicy());
            socket = new DatagramSocket(port);
            final var bufferSize = socket.getReceiveBufferSize();
            connectionsHandler.submit(() -> { while (!socket.isClosed() && !Thread.currentThread().isInterrupted()) {
                try {
                    final var packet = Util.receivePacket(socket, bufferSize);
                    final var msg =  Util.getMessage(packet);
                    final var responseBytes = "Hello, ".concat(msg).getBytes(StandardCharsets.UTF_8);
                    packet.setData(responseBytes);
                    executor.submit(() -> {
                        try {
                            socket.send(packet);
                        } catch (final IOException ex) {
                            handleIOException(ex);
                        }
                    });
                } catch (final IOException ex) {
                    if (!socket.isClosed()) {
                        handleIOException(ex);
                    }
                }
            }});
        } catch (final IOException ex) {
            handleIOException(ex);
        }
    }

    @Override
    public void close() {
        if (socket != null) {
            connectionsHandler.shutdownNow();
            executor.shutdownNow();
            socket.close();
        }
    }
}