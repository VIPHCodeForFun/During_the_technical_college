
import java.util.*;

/** A demo for bit operations */
class BitOpsDemo {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);

        int value = 0;
        System.out.print("Enter a decimal number: ");
        // Read and set value.
        ... // TODO
        System.out.printf("Initial value is %d (0x%x)\n", value, value);

        while (true) {
            System.out.print("What bit operation shall be applied (bitset, bitclr, invert)? ");

            // Read answer, implement switch-statement and apply result.
            ... // TODO

            System.out.printf("Value is %d (0x%x)\n", value, value);

            // Ask user whether to stop.
            ... // TODO
        }
    }
}
