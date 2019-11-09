package queue;
// s = size - count of relevant elements in array
// L = length - length of array
// a[i] - queue array  ∧  i = 0 .. L - 1
// h = head - first element in queue, t = tail - insertion point for next element in queue

// INV: L > h >= 0  ∧  L > t >= 0  ∧  s >= 0
public class ArrayQueueADT {
    private int tail;
    private int head;
    private Object[] elements;
    private static int INITIAL_CAPACITY = 16;

    public ArrayQueueADT() {
        tail = 0;
        head = 0;
        elements = new Object[INITIAL_CAPACITY];
    }
    // POST: L' == 16,  t' == -1,  h' == 0, s' == 0

    // PRE: capacity > 0
    public ArrayQueueADT(int capacity) {
        tail = 0;
        head = 0;
        elements = new Object[capacity];
    }
    // POST: L' == capacity, t' == -1, h' == 0, s' == 0

    // PRE: true
    public static void clear(ArrayQueueADT queue) {
        queue.head = 0;
        queue.tail = 0;
        queue.elements = new Object[INITIAL_CAPACITY];
        //elements = new Object[16]; --> // new array may be necessary in the absence of a large amount of free memory
    }
    // POST: h' == t' == s' ==0, L' == 16
    //       a'[i] == null for i = 0 .. 15

    // PRE: (s > 0)  ∧  (a[h] != null)
    public static Object dequeue(ArrayQueueADT queue) {
        Object tmp = element(queue);
        queue.head = ++queue.head % queue.elements.length;
        // INV: s' == s == 0
        if (size(queue) == 0) {
            // all elements in array irrelevant any more <=> new clear queue
            clear(queue);
        }
        return tmp;
    }
    // POST: (((s' == s - 1 >= 0)  ∧  (h' == (h + 1) mod L)  ∧  (t' == t))  ∨  (s' == h' == t' == 0))
    //       ℝ == a[h]

    // PRE: (s > 0)  ∧  (a[h] != null)
    public static Object element(ArrayQueueADT queue) {
        return queue.elements[queue.head];
    }
    // POST: ℝ == a[h]
    //       a'[i] == a[i] for i = 0 .. L - 1,  s' == s,  h' == h,  t' == t, L' == L

    // INV: s' == s
    // PRE: (enqueue() was called)  ∧  (capacity == s == L - 1)
    private static void ensureCapacity(ArrayQueueADT queue, int capacity) {
        int tmp = size(queue);
        queue.elements = getElements(queue, capacity << 1);
        // a'[i] == a[(i + h) mod L] for i = 0 .. s
        queue.tail = tmp;
        queue.head = 0;
    }
    // POST: (L' == (capacity + 1) * 2)  ∧  (h' == 0)  ∧  (t' == s')

    // PRE: x != null
    public static void enqueue(ArrayQueueADT queue, Object x) {
        if (size(queue) + 1 == queue.elements.length) {
            // s == L - 1
            ensureCapacity(queue, size(queue));
            // L' == L * 2
        }
        // POST: L' >= L > s
        queue.elements[queue.tail] = x;
        queue.tail = ++queue.tail % queue.elements.length;
    }
    // POST: (s' == s + 1)  ∧  (((t' == (t + 1) mod L')  ∧  (s' < L' == L))  ∨  ((L' == L * 2)  ∧  (s == L - 1 == t')))
    //       a'[t] == x

    // PRE: true
    public static boolean isEmpty(ArrayQueueADT queue) {
        return size(queue) == 0;
    }
    // POST: ℝ == (s == 0)
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, h' == h, t' == t, L' == L

    // PRE: true
    public static int size(ArrayQueueADT queue) {
        if (queue.tail >= queue.head) {
            return queue.tail - queue.head;
        } else {
            return queue.elements.length - queue.head + queue.tail;
        }
    }
    // POST: ℝ == s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, h' == h, t' == t


    // PRE: true
    public static Object[] toArray(ArrayQueueADT queue) {
        return getElements(queue, size(queue));
    }
    // POST: ℝ == a[(i + h) mod L] for i = 0 .. s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, t' == t, h' == h

    // PRE: ((toArray() was called)  ∨  (ensureCapacity() was called))  ∧  (capacity >= 0)
    public static Object[] getElements(ArrayQueueADT queue, int capacity) {
        Object[] newQueue = new Object[capacity];
        // b[] - new array
        if (queue.head <= queue.tail) {
            // s == 0  ∨  h <= t
            System.arraycopy(queue.elements, queue.head, newQueue, 0, queue.tail - queue.head);
            // (b[i] == a[j] for j = h .. t - 1,  i = 0 .. s - 1)
        } else {
            // s > 0  ∧  h > t
            System.arraycopy(queue.elements, queue.head, newQueue, 0, queue.elements.length - queue.head);
            // b[i] == a[j] for j = h .. L - 1,  i = 0 .. L - h
            System.arraycopy(queue.elements, 0, newQueue, queue.elements.length - queue.head, queue.tail);
            // b[i] == a[j] for j = 0 .. t - 1,  i = L - h .. L - h + t - 1
        }
        return newQueue;
    }
    // POST: ℝ == b[i] == a[(i + h) mod L] for i = 0 .. s
    //       a'[i] == a[i] for i = 0 .. L - 1
    //       s' == s, L' == L, h' == h, t' == t
}