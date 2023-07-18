package A;

/**
 * Well, well, well, looks like we've got the "vehicle of all vehicles" here
 * with Vehicle being an abstract class!
 * 
 * Vehicle is the kind of class that's all about transportation. It's the
 * foundation for all things that move, from bicycles to cars to airplanes. And
 * being an abstract class means that it's a general concept of what a vehicle
 * should be, without actually being a specific type of vehicle itself.
 */
public class Vehicle {

    private static int generatorID = 0;
    private int id = 0;
    private String color = "none";

    /* Constructors */
    public Vehicle() {
        this.id = generatorID;
        Vehicle.generatorID++;
        this.color = "none";
    }

    public Vehicle(String color) {
        this.id = generatorID;
        Vehicle.generatorID++;
        this.color = color;
    }

    /* Getter & Setter */
    public void setColor(String color) {
        this.color = color;
    }

    public String getColor() {
        return this.color;
    }

    public int getId() {
        return id;
    }

    /* Override methods */
    /**
     * Retunrs description of the class as a String
     */
    @Override
    public String toString() {
        return getClass().getName() + " id: " + this.id + " color: " + this.color;
    }
}
