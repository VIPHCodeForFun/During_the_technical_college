package com.example.fhs;

import java.util.Date;

/** A Student of FHS.
 *
 * A Student is a concrete Person with a student ID.*/
public class Student extends Person {
    /** The largest student ID ever given, or zero otherwise. */
    private static int maxstudid = 0;

    /** The student ID. */
    private int studid;

    /** Create a student with given name.
     *
     * Student ID is automatically given in a unique way. */
    public Student(String name) {
        super(name);
        // Largest ID so far plus 1 is by construction unique.
        this.studid = ++maxstudid;
    }

    /** Create a student with given name and ID.*/
    public Student(String name, int studid) {
        super(name);
        this.studid = studid;
        // Update new largest student ID.
        maxstudid = Math.max(maxstudid, studid);
    }

    @Override
    public String toString() {
        return super.toString() + " and student ID is " + studid;
    }
}
