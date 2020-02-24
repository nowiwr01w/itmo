package ru.ifmo.rain.larionov.walk;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Walk {

    private static final int SIZE = 2048;
    private static final int INIT = 0x811c9dc5;
    private static final int PRIME = 0x01000193;
    private static final int ERROR = 0;

    private static int calculateHash(final String fileName) {
        Path path;
        try {
            path = Paths.get(fileName);
        } catch (InvalidPathException e) {
            System.err.println("Invalid path file: " + fileName);
            return ERROR;
        }
        int count, hashRes = INIT;
        byte[] bytes = new byte[SIZE];
        try (InputStream stream = Files.newInputStream(path)) {
            while ((count = stream.read(bytes)) >= 0) {
                hashRes = getHash(bytes, count, hashRes);
            }
        } catch (IOException e) {
            return ERROR;
        }
        return hashRes;
    }

    private static int getHash(final byte[] bytes, final int count, int hash) {
        for (int i = 0; i < count; i++) {
            byte b = bytes[i];
            hash *= PRIME;
            hash ^= (b & 0xff);
        }
        return hash;
    }

    public static void main(String[] args) {
        if (args == null || args.length != 2 || args[0] == null || args[1] == null) {
            System.err.println("Wrong count of arguments");
            return;
        }
        try {
            if (Paths.get(args[1]).getParent() != null) {
                Files.createDirectory(Paths.get(args[1]).getParent());
            }
        } catch (InvalidPathException e) {
            System.err.println("Invalid path file: " + args[1]);
        } catch (IOException e) {
            System.err.println("Something went wrong while creating file: " + args[1]);
        }
        String curFile;
        try (BufferedReader reader = Files.newBufferedReader(Paths.get(args[0]), StandardCharsets.UTF_8)) {
            try (BufferedWriter writer = Files.newBufferedWriter(Paths.get(args[1]), StandardCharsets.UTF_8)) {
                while ((curFile = reader.readLine()) != null) {
                    writer.write(String.format("%08x", calculateHash(curFile)) + ' ' + curFile + '\n');
                }
            } catch (InvalidPathException e) {
                System.err.println("Invalid path file: " + e.getMessage());
            } catch (IOException e) {
                System.err.println("Something went wrong while reading file: " + e.getMessage());
            }
        } catch (InvalidPathException e) {
            System.err.println("Invalid path file: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("Something went wrong while reading file: " + e.getMessage());
        }
    }
}