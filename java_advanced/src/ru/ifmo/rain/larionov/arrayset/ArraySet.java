package ru.ifmo.rain.larionov.arrayset;

import java.util.*;
import static java.util.Collections.emptyList;

public class ArraySet<T extends Comparable<? super T>> extends AbstractSet<T> implements SortedSet<T> {

    private final List<T> mData;
    private final Comparator<? super T> mComparator;

    public ArraySet() {
        this(emptyList(), null);
    }

    public ArraySet(Collection<T> collection) {
        this(collection, null);
    }

    private ArraySet(List<T> data, Comparator<? super T> comparator) {
        mData = data;
        mComparator = comparator;
    }

    public ArraySet(Collection<T> collection, Comparator<? super T> comparator) {
        mComparator = comparator;
        if (!collection.isEmpty()) {
            TreeSet<T> treeSet = new TreeSet<>(comparator);
            treeSet.addAll(collection);
            mData = List.copyOf(treeSet);
        } else {
            mData = emptyList();
        }
    }

    @Override
    public Iterator<T> iterator() {
        return mData.iterator();
    }

    @Override
    public Comparator<? super T> comparator() {
        return mComparator;
    }

    private int indexOf(T element) {
        int index = Collections.binarySearch(mData, element, mComparator);
        return index >= 0 ? index : inversion(index);
    }

    private int inversion(int index) {
        return -(index + 1);
    }

    @Override
    public SortedSet<T> headSet(T toElement) {
        return subSet(0, indexOf(toElement));
    }

    @Override
    public SortedSet<T> tailSet(T fromElement) {
        return subSet(indexOf(fromElement), mData.size());
    }

    private SortedSet<T> subSetIndexed(T fromElement, T toElement) {
        return subSet(indexOf(fromElement), indexOf(toElement));
    }

    private SortedSet<T> subSet(int from, int to) {
        return new ArraySet<>(mData.subList(from, to), mComparator);
    }

    @Override
    public SortedSet<T> subSet(T fromElement, T toElement) {
        Comparator<? super T> comparator = mComparator != null ? mComparator : Comparator.naturalOrder();
        int comparison = comparator.compare(fromElement, toElement);
        if (comparison > 0) {
            throw new IllegalArgumentException();
        } else if (comparison == 0) {
            return new ArraySet<T>(emptyList(), mComparator);
        } else {
            return subSetIndexed(fromElement, toElement);
        }
    }

    @Override
    public int size() {
        return mData.size();
    }

    @Override
    public T first() {
        checkEmpty();
        return mData.get(0);
    }

    @Override
    public T last() {
        checkEmpty();
        return mData.get(size() - 1);
    }

    private void checkEmpty() {
        if (size() == 0) {
            throw new NoSuchElementException();
        }
    }

    @Override
    public boolean contains(Object object) {
        return Collections.binarySearch(mData, (T) Objects.requireNonNull(object), mComparator) >= 0;
    }
}