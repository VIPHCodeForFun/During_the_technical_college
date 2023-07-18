package B;

import A.*;

public class Producer implements java.lang.Runnable {

    /* Properties */
    private ConcurrentRingBuffer ringBuffer;
    private long producedItems = 0;
    private String name = "Producer";

    /* Constructors */
    Producer(ConcurrentRingBuffer rB) {
        this.ringBuffer = rB;
        producedItems = 0;
    }

    /* Override methods */
    @Override
    public void run() {
        final long threadID = Thread.currentThread().getId();
        try {
            while (!Thread.currentThread().isInterrupted()) {

                // * Push ID into the Ringbuffer */
                this.ringBuffer.push(threadID);
                this.producedItems++;
                System.out.println("[" + threadID + "] produced " + producedItems + "                |");
                java.lang.Thread.sleep(500);
            }

        } catch (java.lang.InterruptedException e) {

        } finally {
            System.out.println("Terminate " + name + " " + threadID + "          |");
        }
    }

}/* End of Producer */