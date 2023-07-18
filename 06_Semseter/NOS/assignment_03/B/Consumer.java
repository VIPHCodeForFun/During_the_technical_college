package B;

import A.*;

public class Consumer implements java.lang.Runnable {
    /* Properties */
    private ConcurrentRingBuffer ringBuffer;
    private long consumedItems = 0;
    private String name = "Consumer";

    /* Constructors */
    Consumer(ConcurrentRingBuffer rB) {
        this.ringBuffer = rB;
        this.consumedItems = 0;
    }

    /* Getter */
    public String getName() {
        return this.name;
    }

    /* Override methods */
    @Override
    public void run() {
        final long threadID = Thread.currentThread().getId();
        try {
            while (!Thread.currentThread().isInterrupted()) {

                this.ringBuffer.pop();
                this.consumedItems++;
                System.out.println("[" + threadID + "] consumed " + consumedItems + "                |");
                java.lang.Thread.sleep(500);
            }

        } catch (java.lang.InterruptedException e) {

        } finally {
            System.out.println("Terminate " + name + " " + threadID + "          |");
        }
    }

}/* End of Consumer */
