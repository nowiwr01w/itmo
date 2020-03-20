package ru.ifmo.rain.larionov.concurrent;

import info.kgeorgiy.java.advanced.concurrent.ScalarIP;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Predicate;
import java.util.function.Supplier;

public class IterativeParallelism implements ScalarIP {

    private static <E, T> T execute(int threads, BiFunction<E, T, T> operation, List<? extends E> list,
                                    BiFunction<T, T, T> join, Supplier<T> supplier) throws InterruptedException {
        int blockCount = (int) Math.ceil(list.size() / (double) threads);
        Result<T> result = new Result<>(supplier.get(), threads, join);
        int left = 0;
        int right = Math.min(left + blockCount, list.size());
        ArrayList<Thread> threadsList = new ArrayList<>();
        for (int threadNum = 0; threadNum < threads; threadNum++) {
            Runnable task = new Task<>(result, list.subList(left, right), operation, threadNum, supplier.get());
            Thread thread = new Thread(task);
            threadsList.add(thread);
            thread.start();
            blockCount = (int) Math.ceil((list.size() - right) / (double) (threads - threadNum - 1));
            left = right;
            right = Math.min(list.size(), right + blockCount);
        }
        for (Thread thread : threadsList) {
            thread.join();
        }
        return result.getValue();
    }

    @Override
    public <T> T maximum(int threads, List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        BiFunction<T, T, T> biFunction = (a, b) -> comparator.compare(a, b) >= 0 ? a : b;
        return execute(threads, biFunction, values, biFunction, () -> values.get(0));
    }

    @Override
    public <T> T minimum(int threads, List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        BiFunction<T, T, T> biFunction = (a, b) -> comparator.compare(a, b) <= 0 ? a : b;
        return execute(threads, biFunction, values, biFunction, () -> values.get(0));
    }

    @Override
    public <T> boolean all(int threads, List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        BiFunction<T, Boolean, Boolean> biFunction = (a, b) -> predicate.test(a) && b;
        return execute(threads, biFunction, values, (a, b) -> a && b, () -> true);
    }

    @Override
    public <T> boolean any(int threads, List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        BiFunction<T, Boolean, Boolean> biFunction = (a, b) -> predicate.test(a) || b;
        return execute(threads, biFunction, values, (a, b) -> a || b, () -> false);
    }
}