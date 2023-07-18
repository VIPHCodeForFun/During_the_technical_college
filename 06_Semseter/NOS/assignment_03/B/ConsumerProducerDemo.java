package B;

import A.*;

import java.io.IOException;
import java.util.ArrayList;
import java.lang.System;

/**
 * A demo of ConcurrentRingBuffer, Consumer and Producer.
 *
 * Starts a number of instances of Consumer and Producer and let them run
 * concurrently against a shared ConcurrentRingBuffer to exchange data.
 */
class ConsumerProducerDemo {
    /** The number of producers to launch. */
    static final int PRODUCER_COUNT = 2;
    /** The number of consumers to launch. */
    static final int CONSUMER_COUNT = 1;
    /** The capacity of the fifo queue. */
    static final int QUEUE_CAPACITY = 6;

    public static void main(String args[]) throws IOException, InterruptedException {
        // The ring buffer to exchange data.
        ConcurrentRingBuffer queue = new ConcurrentRingBuffer(QUEUE_CAPACITY);
        // The list of consumer an producer threads. What looks like a C++
        // template is a so-called generic in Java. An ArrayList is a dynamic
        // array, see the API specification for more details.
        ArrayList<Thread> threads = new ArrayList<Thread>();

        // Creating the producer threads
        for (int i = 0; i < PRODUCER_COUNT; ++i) {
            threads.add(new Thread(new Producer(queue)));
        }

        // Creating the consumer threads
        for (int i = 0; i < CONSUMER_COUNT; ++i)
            threads.add(new Thread(new Consumer(queue)));

        // Starting all threads
        for (Thread thread : threads) {
            thread.start();
        }

        // After queue is cleared, producers can produce in full speed.
        System.out.println("Press any key to clear");
        System.in.read();

        queue.clear();

        System.out.println("Wait until the queue becomes full"); // !! lecuteCode/README.markdown !!
        while (!queue.full()) {
            /* Wait till Que is full */
        }

        // Interrupt threads and wait for threads to terminate
        for (Thread thread : threads) {
            thread.interrupt();
        }
        for (Thread thread : threads) {
            thread.join();
        }

        System.out.println("Shutdown");
    }
}
