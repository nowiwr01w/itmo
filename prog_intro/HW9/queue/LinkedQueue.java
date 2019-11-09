package queue;

public class LinkedQueue extends AbstractQueue {

    private Node tail, head;

    protected void enqueueImpl(Object object) {
        if (size == 1) {
            head = tail = new Node(object, null);
        } else {
            tail.next = new Node(object, null);
            tail = tail.next;
        }
    }


    protected Object elementImpl() {
        return head.value;
    }

    protected void dequeueImpl() {
        head = head.next;
        if (size == 1) {
            tail = null;
        }
    }

    protected void clearImpl() {
        head = tail = null;
    }

    private class Node {
        private Node next;
        private Object value;

        public Node(Object value, Node next) {
            assert value != null;
            this.value = value;
            this.next = next;
        }
    }
}