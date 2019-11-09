package queue;

public class ArrayQueue extends AbstractQueue  {
    private static final int SMALLEST_QUEUE_SIZE = 10;
    private Object[] elements = new Object[SMALLEST_QUEUE_SIZE];
    private int left = 0;
    private int right = 0;

    private int getCapacity() {
        return elements.length;
    }

    private int dec(int x) {
        if (x == 0) {
            return getCapacity() - 1;
        } else {
            return x - 1;
        }
    }

    private int inc(int x) {
        if (x + 1 == getCapacity()) {
            return 0;
        } else {
            return x + 1;
        }
    }

    private void ensureCapacity(int sz) {
        if ((getCapacity() <= sz) || (getCapacity() > sz * 4)) {
            Object[] newElements = new Object[sz * 2 + 1];
            int last;
            if (left <= right) {
                last = right - left;
                System.arraycopy(elements, left, newElements, 0, right - left);
            } else {
                last = getCapacity() - left + right;
                System.arraycopy(elements, left, newElements, 0, getCapacity() - left);
                System.arraycopy(elements, 0, newElements, getCapacity() - left, right);
            }
            elements = newElements;
            left = 0;
            right = last;
        }
    }

    protected void enqueueImpl(Object elem) {
        ensureCapacity(size);
        elements[right] = elem;
        right = inc(right);
    }

    protected Object elementImpl() {
        return elements[left];
    }

    protected void dequeueImpl() {
        assert size > 0;
        elements[left] = null;
        left = inc(left);
    }

    protected void clearImpl() {
        ensureCapacity(SMALLEST_QUEUE_SIZE);
        left = right = 0;
    }
}