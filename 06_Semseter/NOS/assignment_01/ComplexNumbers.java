/*
 * Vidmar Philip
 * [1] https://docs.oracle.com/en/java/javase/13/docs/api/java.base/java/lang/Math.html

 */

import java.lang.Math;
import java.util.Scanner;

/** A demo for complex numbers. */
class ComplexNumbers {

    /**
     * @param args
     */
    public static void main(String args[]) {
        double real = 1;
        double imag = 1;
        double absol = 0;
        double angle = 0;
        double normReal = 0;
        double normImag = 0;
        Scanner scanner = null;

        /* Imput */
        try {
            scanner = new Scanner(System.in);
            System.out.print("Enter real part: ");
            real = scanner.nextDouble();

            System.out.print("Enter imaginary part: ");
            imag = scanner.nextDouble();
        } catch (Exception ex) {
            System.out.println(
                    "Oh no! Your imput has jumped into another dimension and triggered an unexpected error there. Please give it some time to return and try again.");
            ex.printStackTrace(System.out);
            System.out.println(
                    "To ensure that the code is still running, let's just keep going with real and imag values of 1 - because sometimes, you just have to keep the party going!");
        }

        /* Calculate Absolutevalue and Angle */
        absol = Math.sqrt(real * real + imag * imag); // |z| = sqrt( re² + im² )
        angle = Math.acos(real / absol); // pi = arccos( re / |z| )

        System.out.println("Absolute value is " + absol);
        System.out.println("Angle is " + angle);

        /* Normalize the complex number to unit length and output it again. */
        normReal = 1 * Math.cos(angle); // re = 1 * cos(pi)
        normImag = 1 * Math.sin(angle); // im = 1 * sin(pi)

        System.out.println("Normalized real is " + normReal);
        System.out.println("Normalized imag is " + normImag);

        System.out.println("");
        /* Imput */
        try {
            scanner = new Scanner(System.in);
            System.out.print("Enter absolute value: ");
            absol = scanner.nextDouble();

            System.out.print("Enter angle (argument): ");
            angle = scanner.nextDouble();
        } catch (Exception ex) {
            absol = 1;
            angle = 90;
            System.out.println(
                    "Houston, we have an input problem - it seems like the computer is speaking a different language than we are.");
            ex.printStackTrace(System.out);
            System.out.println(
                    "Looks like we're stuck at the intersection of Absolute Avenue and Angle Street, where the values are always 1 and 90 - guess we'll have to make the best of it!");
        }
        scanner.close();
        scanner = null;

        /* Calculate Real and Imag. from new Values */
        real = absol * Math.cos(angle); // re = |z| * cos(pi)
        imag = absol * Math.sin(angle); // im = |z| * sin(pi)

        System.out.println("Real is " + real);
        System.out.println("Imag is " + imag);
    }
}
