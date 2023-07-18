# General comments

Your code style is a mirror of your mind! Use comments where necessary, ask for
clean indentation. If your program does not compile then it receives zero points.


# Assignment 01: Complex numbers

Skim over the API specification of java.lang.Math [1]. Use the methods in this
package to implement the missing code in ComplexNumbers.java.

A test run on this program could look like this:

    Enter real part: 1
    Enter imaginary part: 1
    Absolute value is 1.4142135623730951
    Angle is 0.7853981633974483
    Normalized real is 0.7071067811865475
    Normalized imag is 0.7071067811865475
    Enter absolute value: 2
    Enter angle (argument): 0.78539
    Real is 1.414225107113359
    Imag is 1.4142020175385865


[1] https://docs.oracle.com/en/java/javase/13/docs/api/java.base/java/lang/Math.html


# Assignment 02: BitOpsDemo

Implement the missing code. A test run on this program could like like this:

    Enter a decimal number: 0
    Initial value is 0 (0x0)
    What bit operation shall be applied (bitset, bitclr, invert)? invert
    Value is -1 (0xffffffff)
    Stop? (Y/n) n
    What bit operation shall be applied (bitset, bitclr, invert)? bitclr
    Which bit? 0
    Value is -2 (0xfffffffe)
    Stop? (Y/n) n
    What bit operation shall be applied (bitset, bitclr, invert)? invert
    Value is 1 (0x1)
    Stop? (Y/n) n
    What bit operation shall be applied (bitset, bitclr, invert)? bitset
    Which bit? 2
    Value is 5 (0x5)
    Stop? (Y/n) y


# Assignment 03: Pascal's triangle

Write a program PascalTriangle.java the outputs the Pascal's triangle in the
console. The user is asked how many rows to output. I could be called like
this:

    % java PascalTriangle
    How many rows? 8
                     1
                   1   1
                 1   2   1
               1   3   3   1
             1   4   6   4   1
           1   5  10  10   5   1
         1   6  15  20  15   6   1
       1   7  21  35  35  21   7   1

See [1] for details on how the Pascals triangle is defined. Note that every
number in this scheme is the sum of the two elements above it, like 2 = 1 + 1,
4 = 1 + 3, 6 = 3 + 3, 35  = 15 + 20, and so on.

For the layouting of the triangle it is ok to assume that no number has more
than three digits.

Do not implement or use a method to compute binomial coefficients but compute
the triangle row by row. (A good solution computes each element in constant
time, i.e., if n elements are output than O(n) time is consumed.)

The program PascalTriangle.java can be cleanly implemented in 30-40 lines of
code.

[1]  https://en.wikipedia.org/wiki/Pascal%27s_triangle
