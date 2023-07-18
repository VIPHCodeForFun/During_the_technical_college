package A;

public class Test {
    public static void main(String[] args) throws Exception {
        System.out.println("assignment_03");
        testA();
    }

    public static void testA() {
        try {
            /* Test Ringbuffer */
            ConcurrentRingBuffer Ringbuffer = new ConcurrentRingBuffer(5);
            Ringbuffer.push(new String("A"));
            Ringbuffer.push(new String("B"));
            Ringbuffer.push(new String("C"));
            Ringbuffer.push(new String("D"));
            Ringbuffer.push(new String("E"));
            /* ! Buffer is Full will wait till removed Signal */
            // Ringbuffer.push(new String("F"));
            Ringbuffer.printBufferInfo();

            String ReturnVal = new String((String) Ringbuffer.pop());
            ReturnVal = new String((String) Ringbuffer.pop());
            ReturnVal = new String((String) Ringbuffer.pop());
            ReturnVal = new String((String) Ringbuffer.pop());
            ReturnVal = new String((String) Ringbuffer.pop());
            System.out.println("# ReturnVal = " + ReturnVal);

            Ringbuffer.push(new String("F"));
            Ringbuffer.push(new String("G"));
            Ringbuffer.printBufferInfo();
        } catch (Exception ex) {
            System.out.println("Some Problem");
        } finally {
            System.out.println("finally testA() ");
        }
    }
}
