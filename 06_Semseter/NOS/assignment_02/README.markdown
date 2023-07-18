# General comments

Your code style is a mirror of your mind! Use comments where necessary, take
care for clean indentation. If your program does not compile then it receives
zero points.

Try to use the concepts and mechanisms we learned in the lecture when
appropriate. For instance, use javadoc comments, proper visibility for fields,
package definitions, coding conventions, and so on without being explicitly
mentioned in the assignments.


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


# Assignment B: CarDealership

Add a class `VehicleOwner` with `name`, `birthdate` and `address` as fields.
Make each vehicle to refer to an owner in a suitable way. Also allow for a
vehicle to not be owned.

The field `birthdate` might be a string. However, you may also have a look at
`java.util.Date` if you like.

Add a class `CarDealership` that stores an unlimited number of unowned
vehicles. Add a method `sellVehicle()` that sells a vehicle to an owner, i.e.,
the vehicle leaves the dealership and gets a new owner. Add a method
`buyBackVehicle()` that buys an owned vehicle back to the dealership. Check for
the following _invariant_ within those two methods: Only unowned cars are in
the dealership and cars outside. That is, check that a vehicle to be sold is
now owned and a vehicle to be bought back is owned. (If you like then you can
use exceptions from lecture 03 when invariants are not met. But you do not need
to. It suffices if `sellVehicle()` and `buyBackVehicle()` silently return.)

Have a look at `java.util.ArrayList<E>` to make the implementation
`CarDealership` simpler for you. For a demo have a look at
`com.example.fhs.Lecture` in the lecture-02 demo code.

Make `CarDealership` to be semi-deeply cloneable: The list of vehicles shall be
cloned, too, but the vehicles and owners shall not be cloned (of course).

Add a test program that illustrates and tests `CarDealership`. Use
`VehiclePrinter` where it makes sense. (A unit testing framework like junit
would be in order here, but this is beyond this course.)

You do not need to copy over your solution from assignment A but you can simple
extend it. Consider A and B to be one single project, also regarding package
names.


# Additional remarks

The concept of an _invariant_ is essential to computer science and mathematics,
see
[wikipedia](https://en.wikipedia.org/wiki/Invariant_(mathematics)#Invariants_in_computer_science).
