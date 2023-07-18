class OperatorsDemo {
    public static void main(String args[]) {
        assert 13 + 5 == 18;                // Call java with -ea to enable assertions
        assert 5 / 13 == 0;                 // Integer division
        assert 1.0 / 2.0 == 0.5;            // Be careful: Floating-point equality!
        assert 1.0f + 0.00000001f == 1.0f;  // Numerical errors break exact equality

        //assert 3 >= 2 && 7;               // Syntax error: 7 is not boolean
        //assert 3 == true;                 // Syntax error: cannot compare int and bool
        assert false;                       // We expect that to fail
    }
}
