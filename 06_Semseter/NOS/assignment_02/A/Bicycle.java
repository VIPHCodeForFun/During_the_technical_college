package A;

/**
 * Well, if you ask me, this class is a real "wheely" good time!
 * 
 * You see, Bicycle is like the cooler, sportier cousin of Vehicle. It's the
 * kind of class that likes to zoom around town, feeling the wind in its spokes
 * and the sun on its handlebars. And with that "extends Vehicle" part, you know
 * it's got some serious pedigree -- like it comes from a long line of rad
 * rides.
 * 
 * So yeah, if you're looking for a class that's equal parts practical and
 * playful, Bicycle is the one for you. Just be sure to wear a helmet when
 * you're coding, okay? Safety first!
 * (C-GPT)
 */

public class Bicycle extends Vehicle {

    private int countGears;

    /* Constructors */
    public Bicycle() {
        super();
        this.countGears = 1;
    }

    public Bicycle(String color, int countGears) {
        super(color);
        this.countGears = countGears;
    }

    /* Getter & Setter */
    public void setCountGears(int countGears) {
        this.countGears = countGears;
    }

    public int gettCountDoors() {
        return this.countGears;
    }

    /* Override methods */
    /**
     * Retunrs description of the class as a String
     */
    @Override
    public final String toString() {
        return "" + " id: " + getId()
                + getClass().getName()
                + " Color: " + getColor()
                + " count gears: " + this.countGears;
    }
}
