package com.example.fhs;

import java.util.Date;

/** A Teacher is a concrete Person. */
public class Teacher extends Person {
    public Teacher(String name) {
        super(name);
    }

    public String toString() {
        return super.toString() + ", being teacher.";
    }
}
