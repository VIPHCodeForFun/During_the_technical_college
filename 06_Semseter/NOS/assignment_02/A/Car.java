package A;

/**
 * Looks like we've got a real "driven" class here!
 * 
 * Car is the kind of class that's always in high gear, ready to rev its engine
 * and hit the open road. And with "extends MotorizedVehicle," you know it's got
 * the power to take you places.
 * 
 * So if you're looking for a class that's fast, sleek, and ready to go the
 * distance, Car is the one for you. Just be sure to obey all traffic rules and
 * watch out for any bugs in your code -- you don't want to end up with a "car
 * crash" of a program!
 * (C-GPT)
 */
public class Car extends MotorizedVehicle {

    private int countDoors;

    /* Constructors */
    public Car() {
        super();
        this.countDoors = 1;
    }

    public Car(String color, float enginePower, int countDoors) {
        super(color, enginePower);
        this.countDoors = countDoors;
    }

    /* Getter & Setter */
    public void setCountDoors(int countDoors) {
        this.countDoors = countDoors;
    }

    public int gettCountDoors() {
        return this.countDoors;
    }

    /* Override methods */
    /**
     * Retunrs description of the class as a String
     * ! its only finay for practice !
     */
    @Override
    public final String toString() {
        return "" + " id: " + getId()
                + getClass().getName()
                + " Color: " + getColor()
                + " engine power: " + getEnginePower()
                + " count doors: " + this.countDoors;
    }
}
