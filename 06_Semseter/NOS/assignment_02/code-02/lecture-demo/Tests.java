import com.example.fhs.*;

/** A Test class to test classes of package com.example.fhs. */
class Tests {
    public static void main(String args[]) throws CloneNotSupportedException {
        Student alice = new Student("Alice", 31);
        Student candy = new Student("Candy");
        Student duffy = new Student("Duffy");
        Teacher bob = new Teacher("Bob");

        Lecture nos = new Lecture("NOS", bob);
        nos.enroll(alice);
        nos.enroll(candy);

        Lecture mic = (Lecture) nos.clone();
        mic.setTitle("MIC");
        mic.unroll(candy);
        mic.enroll(duffy);

        System.out.println(nos.toString());
        System.out.println(mic.toString());

        Lecture nos2 = (Lecture) nos.clone();
        System.out.println("nos eq nos2: " + nos.equals(nos2));
        System.out.println("nos eq mic: " + nos.equals(mic));
        System.out.println("Hash codes of nos, nos2 and mic: " +
                           nos.hashCode() + " " +
                           nos2.hashCode() + " " +
                           mic.hashCode());
    }
}
