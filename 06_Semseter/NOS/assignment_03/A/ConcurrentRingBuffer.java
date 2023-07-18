
package A;

import java.util.concurrent.locks.*;

/**
 * A thread-safe implementation of a Ring Buffer data structure.
 * A Ring Buffer is a fixed-size circular buffer that stores data in a FIFO
 * order.
 * When the buffer is full, the oldest data is overwritten by the newest data.
 * Access to the Ring Buffer is locked to prevent data corruption and race
 * conditions in a multi-threaded environment.
 *
 * watch out for single thread applications if the buffer is full or empty it
 * will wait endlessly
 */
public class ConcurrentRingBuffer implements ConcurrentFifoQueue {

    /* Properties */
    /** buffer space */
    private Object[] array;
    /** read-index that points to the array element that is read next by `pop()` */
    private int readIndex = 0;
    /** write-index that points to the array element written next by`push()` */
    private int writeIndex = 0;
    /** Number of elements in the buffer */
    private int elementCount = 0;

    /* Thread locking properties */
    /** Locks an section for a thread */
    private Lock bufferLock = new ReentrantLock();
    /** Condition if something is added from the buffer */
    private Condition added = bufferLock.newCondition();
    /** Condition if something is removed from the buffer */
    private Condition removed = bufferLock.newCondition();

    /* Constructors */
    /**
     * ringbuffer with 256 Objects
     */
    public ConcurrentRingBuffer() {
        array = new Object[256];
        elementCount = 0;
        readIndex = 0;
        writeIndex = 0;
    }

    /**
     * ringbuffer with custom len
     * 
     * @param ringBufferLen
     */
    public ConcurrentRingBuffer(int ringBufferLen) {
        array = new Object[ringBufferLen];
        elementCount = 0;
        readIndex = 0;
        writeIndex = 0;
    }

    /* Methods */
    /** Returns true if no elements are stored. */
    @Override
    public boolean empty() {
        bufferLock.lock(); // Lock for current Thread
        try {
            if (elementCount == 0) {
                return true;
            }
            return false;
        } finally {
            bufferLock.unlock(); // release Lock
        }
    }

    /** Returns true if no further elements can be stored. */
    @Override
    public boolean full() {
        bufferLock.lock(); // Lock for current Thread
        try {
            if (elementCount == array.length) {
                return true;
            }
            return false;
        } finally {
            bufferLock.unlock(); // release Lock
        }
    }

    /**
     * Stores the given object.
     *
     * If full() returns true then this call blocks until full() is not true
     * anymore.
     */
    @Override
    public void push(Object Object) throws InterruptedException {
        bufferLock.lock(); // Lock for current Thread
        try {
            /* blocks until full() is not true */
            while (full()) {
                removed.await(); // wait for Lock signal
            }
            /* Add element */
            elementCount++;
            array[writeIndex] = Object;
            /* Set new Index */
            writeIndex++;
            /* Check if Index is out of bounce */
            int maxIndex = array.length - 1;
            if (writeIndex > maxIndex) {
                writeIndex = 0;
            }
            /* Send signal to all threads that a Element is added */
            added.signalAll();

        } finally {
            bufferLock.unlock(); // release Lock
        }
        return;
    }

    /**
     * Removes the oldes object and returns it.
     *
     * If empty() returns true then this call blocks until empty() is not true
     * anymore.
     */
    @Override
    public Object pop() throws InterruptedException {
        bufferLock.lock(); // Lock for current Thread
        try {
            /* blocks until empty() is not true */
            while (empty()) {
                added.await(); // wait for signal
            }
            /* Save Element in returnObject */
            elementCount--;
            Object returnObject = array[readIndex];
            /* Set new Index */
            readIndex++;
            /* Check if Index is out of bounce */
            int maxIndex = array.length - 1;
            if (readIndex > maxIndex) {
                readIndex = 0;
            }
            /* Send signal to all threads that a Element is removed */
            removed.signalAll();
            return returnObject;

        } finally {
            bufferLock.unlock(); // release Lock
        }
    }

    /**
     * Removes all objects
     */
    @Override
    public void clear() throws InterruptedException {
        bufferLock.lock();
        try {
            /* Set all elements to null */
            for (int index = 0; index < array.length; index++) {
                this.array[index] = null;
            }
            /* Set reset state */
            this.elementCount = 0;
            this.writeIndex = 0;
            this.readIndex = 0;

            removed.signalAll();
        } finally {
            bufferLock.unlock();
        }
    }

    /**
     * Prints information from the Buffer to the Console
     */
    public synchronized void printBufferInfo() {
        System.out.println("Ringbuffer Info:");
        System.out.println("Empty         = " + empty());
        System.out.println("Full          = " + full());
        System.out.println("c. Objects    = " + elementCount);
        System.out.println("readIndex     = " + readIndex);
        System.out.println("writeIndex    = " + writeIndex);
        for (int index = 0; index < array.length; index++) {
            System.out.print(" [" + index + "]");
        }
        System.out.println(" ");
        for (Object object : this.array) {
            if (object != null) {
                System.out.print("-(" + object.toString() + ")");
            } else {
                System.out.print("-(" + "null" + ")");
            }
        }
        System.out.println("-");
    }

} /* End of class */