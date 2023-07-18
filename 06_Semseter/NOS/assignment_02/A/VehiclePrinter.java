package A;

/**
 * Looks like we've got a "print-tastic" class here with VehiclePrinter!
 * 
 * VehiclePrinter is the kind of class that's all about making sure you can see
 * all the important details of a vehicle. It's like a personal assistant for
 * your coding, ready to print out all the information you need to know about a
 * vehicle
 * (C-GPT)
 */
public class VehiclePrinter {

    /**
     * Well, howdy there partner! whe declareed this method as "static", ya don't
     * need no fancy-shmancy instance of the class to call it, no sirree! Ya just go
     * ahead and call it straight up by the class name, and that can sure make yer
     * code simpler and help ya save on memory, 'cause ya don't gotta go and create
     * an instance of that class. Yee-haw, ain't that just a rootin' tootin' time
     * saver?
     * 
     * You can always tell which little kiddo object you're dealing with! That's
     * right, this pillar - called "polymorphism" - lets you work with objects of
     * different classes as if they were all the same class. Niceee.
     * 
     * @param vehicle
     */
    public static void print(Vehicle vehicle) {
        System.out.println("" + vehicle.toString());
    }
}
