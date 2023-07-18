import A.*;
import B.*;
import java.util.ArrayList;

/**
 * Test is the kind of class that's all about having fun and trying out new
 * things. It's like a playground for your coding, a place where you can let
 * your imagination run wild and try out all kinds of crazy ideas.
 * 
 * And with a name like Test, you know this class is all about trial and error.
 * It's the perfect place to experiment with different code snippets and
 * functions, without having to worry about breaking anything important.
 */

public class TestAssingmentB {

    public static void main(String[] args) {
        System.out.println("Test program assingment 2 B");

        /* Create Array for Persons */
        VehicleOwner person[] = {
                new VehicleOwner("Max Mustermann", "15.05.1990", "Musterstraße 1"),
                new VehicleOwner("Sarah Schmidt", "03.09.1985", "Schusterstraße 10"),
                new VehicleOwner("Robert Wagner", "20.11.1975", "Wagnerstraße 5")
        };

        /* Create Lists for dealer vehicles */
        ArrayList<Vehicle> dealerVehicles = new ArrayList<Vehicle>();
        dealerVehicles.add(new Car("rot", 300, 2));
        dealerVehicles.add(new Car("weiß", 200, 5));
        dealerVehicles.add(new Motorcycle("rot", 1100, 1));
        dealerVehicles.add(new Motorcycle("schwarz", 1800, 1));
        dealerVehicles.add(new Bicycle("grau", 24));
        dealerVehicles.add(new Bicycle("grün", 21));

        /* Create Dealer */
        CarDealership carDealer = new CarDealership(dealerVehicles);
        carDealer.printDealerVehicles();

        /* Buy Vehicles */
        System.out.println("/* Buy Vehicles */");
        carDealer.sellVehicle(1, person[0]);
        carDealer.sellVehicle(2, person[1]);
        carDealer.sellVehicle(3, person[2]);

        System.out.println("/* Bob Dealer Cars */");
        carDealer.printDealerVehicles();

        /* Sell Vehicles */
        System.out.println("/* Bob Dealer Cars whats it back */");
        carDealer.buyBackVehicle(null);
        carDealer.buyBackVehicle(person[0]);

        System.out.println("/* Bob Dealer Cars */");
        carDealer.printDealerVehicles();
    }
}
