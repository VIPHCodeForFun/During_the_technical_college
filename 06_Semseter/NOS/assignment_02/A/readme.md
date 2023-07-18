# extend Assignment A
author: @Philipp Vidmar

package veh;
    /* package-private */
        Vehicle.java
        MotorizedVehicle.java

    /* public */
        Bicycle.java
        Car.java
        Motorcycle.java
        VehiclePrinter.java     
-----------------------------------------------------------------------------------

# Assignment A: Vehicle class hierarchy

Design an implement a class hierarchy for different kind of vehicles: `Vehicle,
MotorizedVehicle, Car, Motorcycle, Bicycle`. Make a reasonable decision on
inheritance.

Add (at least) these fields to classes:

* `Vehicle` has a string `color`.
* `MotorizedVehicle` has a floating-point field `enginePower`.
* `Car` has an integral field `countDoors`.
* `Motorcycle` has an integral field `countStroke`.
* `Bicycle` has an integral field `countGears`.

Choose suitable modifiers (e.g., access specifiers) for all fields, methods,
and classes. Make classes abstract if it makes sense and comment on your
reasoning. That is, argue for it in a Java comment. Add suitable constructors.

Override `java.lang.Object.toString()` that returns a string that describes
objects.

Add a class `VehiclePrinter` that provides a method `print(Vehicle)` by using
`Vehicle.toString()`. Make a design decision whether to make `print(Vehicle)`
static and comment on your reasoning.

Follow the class design guidelines we talked about in the lecture.


