package ru.ifmo.rain.larionov.concurrent;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;

class Result<T> {
    private T value;
    private List<T> results;
    private BiFunction<T, T, T> biFunction;

    public Result(T value, int size, BiFunction<T, T, T> biFunction) {
        this.value = value;
        this.results = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            results.add(null);
        }
        this.biFunction = biFunction;
    }

    public T getValue() {
        for (T result : results) {
            value = biFunction.apply(value, result);
        }
        return value;
    }

    public void modify(T t, int threadNum) {
        results.set(threadNum, t);
    }
}
