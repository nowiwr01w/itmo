package queue;
// s = size - count of relevant elements in array
// L = length - length of array
// a[i] - queue array  ∧  i = 0 .. L - 1
// h = head - first element in queue, t = tail - insertion point for next element in queue

// INV: L > h >= 0  ∧  L > t >= 0  ∧  s >= 0
public class ArrayQueueModule {
    private static int tail = 0;
    private static int head = 0;
    private static int INITIAL_CAPACITY = 16;
    private static Object[] elements = new Object[16];

    // PRE: true
    public static void clear() {
        head = 0;
        tail = 0;
        elements = new Object[INITIAL_CAPACITY];
        //elements = new Object[16]; --> // new array may be necessary in the absence of a large amount of free memory
    }
    // POST: h' == t' == s' ==0, L' == 16
    //       a'[i] == null for i = 0 .. 15

    // PRE: (s > 0)  ∧  (a[h] != null)
    public static Object dequeue() {
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
    public static Object element() {
        return elements[head];
    }
    // POST: ℝ == a[h]
    //       a'[i] == a[i] for i = 0 .. L - 1,  s' == s,  h' == h,  t' == t, L' == L

    // INV: s' == s
    // PRE: (enqueue() was called)  ∧  (capacity == s == L - 1)
    private static void ensureCapacity(int capacity) {
        int tmp = size();
        elements = getElements(2 * capacity, 0);
        // a'[i] == a[(i + h) mod L] for i = 0 .. s
        tail = tmp;
        head = 0;
    }
    // POST: (L' == (capacity + 1) * 2)  ∧  (h' == 0)  ∧  (t' == s')

    // PRE: x != null
    public static void enqueue(Object x) {
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
    public static boolean isEmpty() {
        return size() == 0;
    }
    // POST: ℝ == (s == 0)
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, h' == h, t' == t, L' == L

    // PRE: true
    public static int size() {
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
    public static Object[] toArray() {
        return getElements(size(), 0);
    }
    // POST: ℝ == a[(i + h) mod L] for i = 0 .. s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, t' == t, h' == h

    // PRE: ((toArray() was called)  ∨  (ensureCapacity() was called))  ∧  (capacity >= 0)
    public static Object[] getElements(int capacity, int inPoint) {
        Object[] newQueue = new Object[capacity];
        // b[] - new array
        if (head <= tail) {
            // s == 0  ∨  h <= t
            System.arraycopy(elements, head, newQueue, inPoint, tail - head);
            // (b[i] == a[j] for j = h .. t - 1,  i = 0 .. s - 1)
        } else {
            // s > 0  ∧  h > t
            System.arraycopy(elements, head, newQueue, inPoint, elements.length - head);
            // b[i] == a[j] for j = h .. L - 1,  i = 0 .. L - h
            System.arraycopy(elements, 0, newQueue, elements.length - head + inPoint, tail);
            // b[i] == a[j] for j = 0 .. t - 1,  i = L - h .. L - h + t - 1
        }
        return newQueue;
    }
    // POST: ℝ == b[i] == a[(i + h) mod L] for i = 0 .. s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, h' == h, t' == t
}