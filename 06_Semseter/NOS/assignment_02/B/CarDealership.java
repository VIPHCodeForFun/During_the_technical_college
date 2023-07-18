package B;

import A.*;
import java.util.ArrayList;

/**
 * Yo, this class called CarDealership is the dealio in package B, you feel me?
 * It's got some dope methods for buying and selling cool rides.
 */
public class CarDealership {

    /* Variables */
    private ArrayList<Vehicle> dealerVehicles;

    /* Methods */
    /**
     * The sellVehicle function sells a vehicle from a car dealer to a vehicle
     * owner.
     * 
     * @param vehicleId
     * @param vehicleOwner
     * @return True if Vehicle id is found
     */
    public boolean sellVehicle(int vehicleId, VehicleOwner vehicleOwner) {

        /* Check for Valid imput */
        if (vehicleOwner == null) {
            System.out.println("Looks like you sell a car to Mr. Null Nobody!!");
            return false;
        }

        /* Check if Owner has a Car */
        if (vehicleOwner.getVehicle() != null) {
            System.out.println("I can only sell you a car if you don`t have any!! ");
            return true;
        }

        /* Find Vehicle by ID */
        for (int index = 0; index < dealerVehicles.size(); index++) {

            Vehicle dealerVehicle = dealerVehicles.get(index);

            if (vehicleId == dealerVehicle.getId()) {
                /* Set vehicle Owner new Vehicle and clear it from car dealer */
                vehicleOwner.setVehicle(dealerVehicle);
                dealerVehicles.remove(index);
                return true;
            }
        }
        /* Nothing found */
        return false;
    }

    /**
     * This is a wild and crazy function called buyBackVehicle in the CarDealership
     * class. It receives a VehicleOwner object and responds with a boolean value.
     * 
     * @param vehicleOwner
     * @return
     */
    public boolean buyBackVehicle(VehicleOwner vehicleOwner) {
        /* Check for Valid imput */
        if (vehicleOwner == null) {
            System.out.println("Looks like you want to buy a vehicle from Mr. Null Nobody!!");
            return false;
        }

        dealerVehicles.add(vehicleOwner.getVehicle());
        vehicleOwner.setVehicle(null);
        return true;
    }

    /**
     * The printDealerVehicles function prints the list of vehicles currently
     * available in the car dealer's inventory.
     */
    public void printDealerVehicles() {
        for (Vehicle vehicle : dealerVehicles) {
            VehiclePrinter.print(vehicle);
        }
    }

    /* Constructors */
    public CarDealership() {
        this.dealerVehicles = new ArrayList<Vehicle>();
    }

    public CarDealership(ArrayList<Vehicle> dealerVehicles) {
        this.dealerVehicles = dealerVehicles;
    }

    /* Getter methods */

    /* Setter methods */

}
