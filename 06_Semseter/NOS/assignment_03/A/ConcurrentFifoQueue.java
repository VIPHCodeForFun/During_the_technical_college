package A;

/**
 * A concurrent concurrent FIFO queue.
 *
 * It is a first-in-first-out queue that supports concurrent access. It
 * essentially provides the operations push() to put an object in and pop() to
 * get an object out.
 *
 * If the queue has fixed capacity and it is full and a thread tries to push()
 * an object then it is blocked until an object is removed from the queue. Vice
 * versa, if a thread tries to pop() an object out and the queue is empty then
 * it is blocked until another thread put an object in.
 *
 * ConcurrentRingBuffer implements the ConcurrentFifoQueue interface.
 */
interface ConcurrentFifoQueue {
    /** Returns true if no elements are stored. */
    public boolean empty();

    /** Returns true if no further elements can be stored. */
    public boolean full();

    /**
     * Stores the given object.
     *
     * If full() returns true then this call blocks until full() is not true
     * anymore.
     */
    public void push(Object o) throws InterruptedException;

    /**
     * Removes the oldes object and returns it.
     *
     * If empty() returns true then this call blocks until empty() is not true
     * anymore.
     */
    public Object pop() throws InterruptedException;

    /** Removes all objects. */
    public void clear() throws InterruptedException;
}
