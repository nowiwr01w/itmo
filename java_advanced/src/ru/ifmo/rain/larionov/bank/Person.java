package ru.ifmo.rain.larionov.bank;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Person extends Remote {

    int getPassportId() throws RemoteException;

    String getFirstName() throws RemoteException;

    String getLastName() throws RemoteException;
}
