package B;

import A.*;

/**
 * 
 */
public class VehicleOwner {

    private String name = "Nobody";
    private String birthdate = "01.01.2022";
    private String address = "Anystreet 0";

    private Vehicle vehicle = null;

    /* Constructors */
    public VehicleOwner() {
        this.name = "Nobody";
        this.birthdate = "01.01.2022";
        this.address = "Anystreet 0";
        this.vehicle = null;
    };

    public VehicleOwner(String name, String birthdate, String address) {
        this.name = name;
        this.birthdate = birthdate;
        this.address = address;
        this.vehicle = null;
    };

    /* Getter methods */
    public String getName() {
        return this.name;
    }

    public String getBirthdate() {
        return this.birthdate;
    }

    public String getAddress() {
        return this.address;
    }

    public Vehicle getVehicle() {
        return this.vehicle;
    }

    /* Setter methods */
    public void setName(String name) {
        this.name = name;
    }

    public void setBirthdate(String birthdate) {
        this.birthdate = birthdate;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setVehicle(Vehicle vehicle) {
        this.vehicle = vehicle;
    }
}
