package queue;
// s = size - count of relevant elements in array
// L = length - length of array
// a[i] - queue array  ∧  i = 0 .. L - 1
// h = head - first element in queue, t = tail - insertion point for next element in queue

// INV: L > h >= 0  ∧  L > t >= 0  ∧  s >= 0
public class ArrayQueue {
    private int tail;
    private int head;
    private Object[] elements;
    private int INITIAL_CAPACITY = 16;

    public ArrayQueue() {
        tail = 0;
        head = 0;
        elements = new Object[INITIAL_CAPACITY];
    }
    // POST: L' == 16,  t' == h' == s' == 0

    // PRE: capacity > 0
    public ArrayQueue(int capacity) {
        tail = 0;
        head = 0;
        elements = new Object[capacity];
    }
    // POST: L' == capacity, t' == h' == s' == 0

    // PRE: true
    public void clear() {
        head = 0;
        tail = 0;
        elements = new Object[INITIAL_CAPACITY];
        //elements = new Object[16]; --> // new array may be necessary in the absence of a large amount of free memory
    }
    // POST: h' == t' == s' ==0, L' == 16
    //       a'[i] == null for i = 0 .. 15

    // PRE: (s > 0)  ∧  (a[h] != null)
    public Object dequeue() {
        Object tmp = element();
        head = ++head % elements.length;
        // INV: s' == s == 0
        if (size() == 0) {
            // all elements in array irrelevant any more <=> new clear queue
            clear();
        }
        return tmp;
    }
    // POST: (((s' == s - 1 >= 0)  ∧  (h' == (h + 1) mod L)  ∧  (t' == t))  ∨  (s' == h' == t' == 0))
    //       ℝ == a[h]

    // PRE: (s > 0)  ∧  (a[h] != null)
    public Object element() {
        return elements[head];
    }
    // POST: ℝ == a[h]
    //       a'[i] == a[i] for i = 0 .. L - 1,  s' == s,  h' == h,  t' == t, L' == L

    // INV: s' == s
    // PRE: (enqueue() was called)  ∧  (capacity == s == L - 1)
    private void ensureCapacity(int capacity) {
        int tmp = size();
        elements = getElements(capacity << 1);
        // a'[i] == a[(i + h) mod L] for i = 0 .. s
        tail = tmp;
        head = 0;
    }
    // POST: (L' == (capacity + 1) * 2)  ∧  (h' == 0)  ∧  (t' == s')

    // PRE: x != null
    public void enqueue(Object x) {
        if (size() + 1 == elements.length) {
            // s == L - 1
            ensureCapacity(size());
            // L' == L * 2
        }
        // POST: L' >= L > s
        elements[tail] = x;
        tail = ++tail % elements.length;
    }
    // POST: (s' == s + 1)  ∧  (((t' == (t + 1) mod L')  ∧  (s' < L' == L))  ∨  ((L' == L * 2)  ∧  (s == L - 1 == t')))
    //       a'[t] == x

    // PRE: true
    public boolean isEmpty() {
        return size() == 0;
    }
    // POST: ℝ == (s == 0)
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, h' == h, t' == t, L' == L

    // PRE: true
    public int size() {
        if (tail >= head) {
            return tail - head;
        } else {
            return elements.length - head + tail;
        }
    }
    // POST: ℝ == s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, h' == h, t' == t

    // PRE: true
    public Object[] toArray() {
        return getElements(size());
    }
    // POST: ℝ == a[(i + h) mod L] for i = 0 .. s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, t' == t, h' == h

    // PRE: ((toArray() was called)  ∨  (ensureCapacity() was called))  ∧  (capacity >= 0)
    public Object[] getElements(int capacity) {
        Object[] newQueue = new Object[capacity];
        // b[] - new array
        if (head <= tail) {
            // s == 0  ∨  h <= t
            System.arraycopy(elements, head, newQueue, 0, tail - head);
            // (b[i] == a[j] for j = h .. t - 1,  i = 0 .. s - 1)
        } else {
            // s > 0  ∧  h > t
            System.arraycopy(elements, head, newQueue, 0, elements.length - head);
            // b[i] == a[j] for j = h .. L - 1,  i = 0 .. L - h
            System.arraycopy(elements, 0, newQueue, elements.length - head, tail);
            // b[i] == a[j] for j = 0 .. t - 1,  i = L - h .. L - h + t - 1

        }
        return newQueue;
    }
    // POST: ℝ == b[i] == a[(i + h) mod L] for i = 0 .. s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, h' == h, t' == t

}