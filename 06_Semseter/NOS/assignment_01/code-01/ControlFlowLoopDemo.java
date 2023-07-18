class ControlFlowDemo {
    public static void main(String args[]) {
        System.out.println("Fibonacci series …");
        int a = 1, b = 0;
        while (b < 100) {               // Each block {} defines a scope for variables
            System.out.print(b);
            System.out.print(" ");

            int c = a + b;              // A variable lives only within is scope
            b = a;
            a = c;
        }                               // c does not live outside this block
        System.out.println();

        int n = 1;
        int fac = 5;
        for (int i = 1; i <= fac; ++i)
            n *= i;
        System.out.printf("%d factorial is %d\n", fac, n);
    }                                   // a, b does not live outside this block
}
