package com.example.fhs;

import java.util.Date;

/** A an abstract Person.
 *
 * Typical concrete subclasses are Student and Teacher.*/
abstract class Person {
    /** The person's name. */
    private String name;

    /** Create a Person with given anme. */
    public Person(String name) {
        this.name = name;
    }

    /** Getter of name. */
    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Name is " + name;
    }
}
