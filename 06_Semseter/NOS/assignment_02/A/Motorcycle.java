package A;

/**
 * Hold onto your helmets, because we've got a "wild ride" of a class with
 * Motorcycle extending MotorizedVehicle!
 * 
 * Motorcycle is the kind of class that's all about living life on the edge.
 * It's the rebel of the vehicle world, with a fierce attitude and a need for
 * speed. And with "extends MotorizedVehicle," you know it's got the horsepower
 * to back up its bad-boy image.
 * 
 * So if you're looking for a class that's edgy, daring, and ready to tear up
 * the pavement, Motorcycle is the one for you. Just make sure you've got your
 * coding safety gear on, because things can get pretty wild in this class!
 * (C-GPT)
 */
public class Motorcycle extends MotorizedVehicle {

    private int countStroke;

    /* Constructors */
    public Motorcycle() {
        super();
        this.countStroke = 1;
    }

    public Motorcycle(String color, float enginePower, int countStroke) {
        super(color, enginePower);
        this.countStroke = countStroke;
    }

    /* Getter & Setter */
    public void setCountStroke(int countStroke) {
        this.countStroke = countStroke;
    }

    public int gettCountDoors() {
        return this.countStroke;
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
                + " count stroke: " + this.countStroke;
    }
}
