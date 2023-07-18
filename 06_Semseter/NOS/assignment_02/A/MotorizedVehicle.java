package A;

/**
 * Ah, we've got an "abstract" concept here with MotorizedVehicle extending
 * Vehicle!
 * 
 * MotorizedVehicle is the kind of class that's all about power and versatility.
 * It's a vehicle with a motor, which means it's ready to take you places
 * quickly and efficiently. And with "extends Vehicle," you know it's got all
 * the basic features of a standard vehicle.
 * 
 * But being an abstract class means that MotorizedVehicle is a bit of a
 * mystery, too. It's like a blueprint for what a motorized vehicle should be,
 * without actually being a full-fledged vehicle itself. It's up to other
 * classes to fill in the details and bring MotorizedVehicle to life.
 * 
 * So if you're looking for a class that's both powerful and enigmatic,
 * MotorizedVehicle is the one for you. Just be prepared to do some creative
 * thinking and fill in the blanks!
 * (C-GPT)
 */
abstract class MotorizedVehicle extends Vehicle {

    private float enginePower;

    /* Constructors */
    public MotorizedVehicle() {
        super();
        this.enginePower = 1f;
    }

    public MotorizedVehicle(String color, float enginePower) {
        super(color);
        this.enginePower = enginePower;
    }

    /* Getter & Setter */
    public void setEnginePower(float enginePower) {
        this.enginePower = enginePower;
    }

    public float getEnginePower() {
        return this.enginePower;
    }

    /* Override methods */
    /**
     * Retunrs description of the class as a String
     */
    @Override
    public String toString() {
        return getClass().getName()
                + " Color: " + getColor()
                + " engine power: " + this.enginePower;
    }
}