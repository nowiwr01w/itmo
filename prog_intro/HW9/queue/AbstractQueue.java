package queue;

abstract public class AbstractQueue implements Queue {

    protected int size;

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    abstract protected void enqueueImpl(Object e);

    public void enqueue(Object elem) {
        assert elem != null;
        size++;
        enqueueImpl(elem);
    }

    abstract protected Object elementImpl();

    public Object element() {
        assert size > 0;
        return elementImpl();
    }

    abstract protected void dequeueImpl();

    public Object dequeue() {
        Object temp = element();
        dequeueImpl();
        size--;
        return temp;
    }

    abstract protected void clearImpl();

    public void clear() {
        clearImpl();
        size = 0;
    }

    public Object[] toArray() {
        Object[] temp = new Object[size()];
        for (int i = 0; i < size(); i++) {
            temp[i] = dequeue();
            enqueue(temp[i]);
        }
        return temp;
    }
}