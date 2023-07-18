/** The Java language knows exactly eight primitive types. */
class PrimitiveTypeDemo {
    public static void main(String args[]) {
        byte  a = -0x0a;      // A signed 8-bit integer. Hex literals as in C.
        short b = 0b1010;     // A signed 16-bit integer. Binary literals since Java 7.
        int   c = 1_000_000;  // A signed 32-bit integer. Underscores since Java 7.
        long  d = 42L;        // A signed 64-bit integer. Long literals by suffix L.

        float  e = 3.1416f;   // IEEE 754 single-precision floating-point number.
        double f = 1.256e-6;  // IEEE 754 double-precision floating-point number.

        char g    = '€';      // A character. (Actually, a UTF-16 code unit.)
        boolean h = true;     // There is only true or false, and no third!

        System.out.printf("%d %d %d %d %f %f %c %b\n", a, b, c, d, e, f, g, h);
    }
}
