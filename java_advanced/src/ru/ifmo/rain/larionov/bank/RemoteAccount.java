package ru.ifmo.rain.larionov.bank;

public class RemoteAccount implements Account {
    private final String id;
    private int money;

    public RemoteAccount(final String id) {
        this.id = id;
        money = 0;
    }

    public RemoteAccount(final String id, final int money) {
        this.id = id;
        this.money = money;
    }

    @Override
    public String getId() {
        return id;
    }

    @Override
    public synchronized int getMoney() {
        System.out.println("Getting amount of money for account " + id);
        return money;
    }

    @Override
    public synchronized void setMoney(int money) {
        System.out.println("Setting amount of money for account " + id);
        this.money = money;
    }
}
