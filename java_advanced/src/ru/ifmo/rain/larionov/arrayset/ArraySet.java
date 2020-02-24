package ru.ifmo.rain.larionov.arrayset;

import java.util.*;

public class ArraySet<T> extends AbstractSet<T> implements SortedSet<T> {
    private final List<T> data;
    private final Comparator<? super T> comparator;

    public ArraySet() {
        data = Collections.emptyList();
        comparator = null;
    }

    public ArraySet(Collection<T> data) {
        Set<T> treeSet = new TreeSet<>(data);
        this.data = new ArrayList<>(treeSet);
        comparator = null;
    }

    public ArraySet(Comparator<? super T> comparator) {
        data = Collections.emptyList();
        this.comparator = comparator;
    }

    public ArraySet(Collection<T> data, Comparator<? super T> comparator) {
        TreeSet<T> treeSet = new TreeSet<>(comparator);
        treeSet.addAll(data);
        this.data = new ArrayList<>(treeSet);
        this.comparator = comparator;
    }

    private ArraySet(List<T> data, Comparator<? super T> comparator) {
        this.data = data;
        this.comparator = comparator;
    }

    private ArraySet<T> emptySet(Comparator<? super T> comparator) {
        return new ArraySet<T>(comparator);
    }

    private boolean checkInd(int ind) {
        return 0 <= ind && ind <= size();
    }

    private int getInd(T t) {
        int result = Collections.binarySearch(data, Objects.requireNonNull(t), comparator);
        if (result < 0) {
            result = -result - 1;
            if (result == size()) {
                return result;
            }
        }
        return checkInd(result) ? result : -1;
    }

    @SuppressWarnings("unchecked")
    private int compare(T e1, T e2) {
        return comparator() == null ? ((Comparable<? super T>) e1).compareTo(e2) : comparator().compare(e1, e2);
    }

    @Override
    public Iterator<T> iterator() {
        return Collections.unmodifiableList(data).iterator();
    }

    @Override
    public int size() {
        return data.size();
    }


    @Override
    public boolean isEmpty() {
        return data.isEmpty();
    }

    @SuppressWarnings("unchecked")
    @Override
    public boolean contains(Object o) {
        return Collections.binarySearch(data, (T) Objects.requireNonNull(o), comparator) >= 0;
    }


    @Override
    public Comparator<? super T> comparator() {
        return comparator;
    }

    private SortedSet<T> subSet(T fromElement, T toElement, boolean includeLast) {

        int l = getInd(fromElement);
        int r = getInd(toElement);
        if (includeLast && r >= 0) {
            r++;
        }
        if (l == -1 || r == -1 || l >= r) {
            return emptySet(comparator);
        }

        return new ArraySet<>(data.subList(l, r), comparator);
    }

    @Override
    public SortedSet<T> subSet(T fromElement, T toElement) {
        if (compare(fromElement, toElement) > 0) {
            throw new IllegalArgumentException("Start element is greater than end element");
        }
        return subSet(fromElement, toElement, false);
    }

    @Override
    public SortedSet<T> headSet(T toElement) {
        if (data.isEmpty()) {
            return emptySet(comparator);
        }
        return subSet(first(), toElement, false);
    }

    @Override
    public SortedSet<T> tailSet(T fromElement) {
        if (data.isEmpty()) {
            return emptySet(comparator);
        }
        return subSet(fromElement, last(), true);
    }

    private void checkEmpty() {
        if (data.isEmpty()) {
            throw new NoSuchElementException("ArraySet is empty");
        }
    }

    @Override
    public T first() {
        checkEmpty();
        return data.get(0);
    }

    @Override
    public T last() {
        checkEmpty();
        return data.get(size() - 1);
    }
}
