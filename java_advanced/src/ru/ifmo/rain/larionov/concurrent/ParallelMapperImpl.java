package ru.ifmo.rain.larionov.concurrent;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.function.Function;

public class ParallelMapperImpl implements ParallelMapper {

    private static final int MAX = 32;

    private final Lock lock;
    private final List<Thread> threads;
    private final Queue<Runnable> tasks;
    private final Condition queueNotFull;
    private final Condition queueNotEmpty;

    public ParallelMapperImpl(int threadsNumber) {
        if (threadsNumber < 1) {
            throw new IllegalArgumentException("Wrong count of threads.");
        }
        lock = new ReentrantLock(); // позволяет потокам входить в блокировку на ресурсе более одного раза
        tasks = new ArrayDeque<>();
        threads = new ArrayList<>(threadsNumber);
        queueNotFull = lock.newCondition(); // возвращает объект Condition, который связан с текущей блокировкой.
        queueNotEmpty = lock.newCondition(); // Объект Condition позволяет управлять блокировкой.
        execute(threadsNumber);
    }

    private void execute(int threadsNumber) {
        for (int i = 0; i < threadsNumber; i++) {
            Thread thread = new Thread(() -> {
                Runnable task;
                while (!Thread.interrupted()) { // Если поток не прерван
                    lock.lock(); // Устанавливаем блокировку
                    try {
                        while (tasks.isEmpty()) {
                            try {
                                queueNotEmpty.await(); // Если соблюдается условие, то поток ожидает, пока условие не изменится
                            } catch (InterruptedException ignored) {
                                return;
                            }
                        }
                        task = tasks.poll(); // Берём новую таску
                        queueNotFull.signalAll(); // Говорим всем потокам, у которых ранее был вызван метод await(), что они могут продолжить работу
                    } finally {
                        lock.unlock(); // Снимаем блокировку
                    }
                    task.run();
                }
            });
            thread.start();
            threads.add(thread);
        }
    }

    // CountDownLatch позволяет нам координировать выполнение потоков
    private <T, R> void addTask(Function<? super T, ? extends R> f, T arg, int index, List<R> result, CountDownLatch countDownLatch) throws InterruptedException {
        lock.lock(); // Устанавливаем блокировку
        try {
            while (tasks.size() == MAX) { // Решили выделить максимальный размер очереди задач, которые могут выполняться одновременно
                queueNotFull.await(); // Поток ждёт, пока какая-нибудь задача завершится, чтобы можно было продолжать работу
            }
            tasks.add(() -> { // Теперь можно добавить новую таску
                result.set(index, f.apply(arg)); // Которая вычисляет функцию F и записывает значение в Result
                countDownLatch.countDown(); // Результат вычеслен, можем уменьшить значение на 1
            });
            queueNotEmpty.signalAll(); // Говорим всем потокам, у которых ранее был вызван метод await(), что они могут продолжить работу
        } finally {
            lock.unlock(); // Снимаем блокировку
        }
    }

    @Override
    public <T, R> List<R> map(Function<? super T, ? extends R> f, List<? extends T> args) throws InterruptedException {
        List<R> result = new ArrayList<>(Collections.nCopies(args.size(), null));
        var countDownLatch = new CountDownLatch(args.size());
        for (var i = 0; i < args.size(); i++) {
            addTask(f, args.get(i), i, result, countDownLatch);
        }
        countDownLatch.await(); // Метод await() блокирует поток, вызвавший его, до тех пор, пока
        return result;          // счетчик CountDownLatch не станет равен 0
    }

    @Override
    public void close() {
        threads.forEach(Thread::interrupt); // помечаем потоки как прерванные
        for (var thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException ignored) { }
        }
    }
}