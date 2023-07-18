import java.util.concurrent.ArrayBlockingQueue;

class ConcurrentRingBuffer implements ConcurrentFifoQueue {
    ArrayBlockingQueue<Object> queue;
    int cap;

    public ConcurrentRingBuffer(int capacity) {
        queue = new ArrayBlockingQueue<Object>(capacity);
        cap = capacity;
    }

    public int capacity() {
        return cap;
    }

    public int size() {
        return queue.size();
    }

    public boolean empty() {
        return queue.isEmpty();
    }

    public boolean full() {
        return queue.remainingCapacity() == 0;
    }

    public void push(Object o) throws InterruptedException {
        queue.put(o);
    }

    public Object pop() throws InterruptedException {
        return queue.remove();
    }

    public void clear() throws InterruptedException {
        queue.clear();
    }
}
