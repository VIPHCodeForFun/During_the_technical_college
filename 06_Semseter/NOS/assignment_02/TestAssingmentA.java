import A.*;

/**
 * Test is the kind of class that's all about having fun and trying out new
 * things. It's like a playground for your coding, a place where you can let
 * your imagination run wild and try out all kinds of crazy ideas.
 * 
 * And with a name like Test, you know this class is all about trial and error.
 * It's the perfect place to experiment with different code snippets and
 * functions, without having to worry about breaking anything important.
 */

public class TestAssingmentA {

    public static void main(String[] args) {
        System.out.println("Test program assingment 2 A");

        Car auto1 = new Car();
        Car auto2 = new Car("black", 50, 3);

        Motorcycle moped1 = new Motorcycle();
        Motorcycle moped2 = new Motorcycle("yellow", 5, 2);

        Bicycle rad1 = new Bicycle();
        Bicycle rad2 = new Bicycle("red", 8);

        VehiclePrinter.print(auto1);
        VehiclePrinter.print(auto2);
        VehiclePrinter.print(moped1);
        VehiclePrinter.print(moped2);
        VehiclePrinter.print(rad1);
        VehiclePrinter.print(rad2);
    }
}
