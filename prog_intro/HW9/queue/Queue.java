package queue;

public interface Queue {
    //R - result
    //n - size

    //pre: true
    //post: R = n
    int size();

    // pre: elem != null
    // post: (n' == n + 1) && (a'[i] == a[i] for i = 0..n - 1) && (a'[n] == elem)
    void enqueue(Object e);

    // pre: n > 0
    // post: R = a[0]
    Object element();

    // pre: n > 0
    // post: (n' == n - 1) && (a'[i - 1] == a[i] for i = 1...n - 1) && (R == a[0])
    Object dequeue();

    //pre: true
    //post: R = (n == 0)
    boolean isEmpty();

    //pre: true
    //post: n` == 0
    void clear();

    //pre: true
    //post: R = a[]
    Object[] toArray();
}