package com.example.fhs;

import java.util.ArrayList;
import java.util.Objects;

/** A Lecture given by a Teacher and attended by list of Students.
 *
 *
 * @author Stefan Huber
 */
public class Lecture implements Cloneable {
    /** The title of the lecture. */
    private String title;
    /** The teacher giving the lecture. */
    private Teacher teacher;
    /** The enrolled students of this lecture. */
    private ArrayList<Student> students = new ArrayList<Student>();

    /** Creates a lecture with given title and teacher.
     *
     * Initially no students have enrolled. */
    public Lecture(String title, Teacher teacher) {
        this.title = title;
        this.teacher = teacher;
    }

    /** Setter of title. */
    public void setTitle(String title) {
        this.title = title;
    }

    /** Getter of title. */
    public String getTitle() {
        return title;
    }

    /** Enroll a new student.
     *
     * If student is already enrolled then do nothing. Takes O(n) time. */
    public void enroll(Student stud) {
        if (!students.contains(stud))
            students.add(stud);
    }

    /** Unroll a student.
     *
     * If student is not enrolled then do nothing. Takes O(n) time. */
    public void unroll(Student stud) {
        students.remove(stud);
    }

    /** Gives a semi-deep copy of Lecture.
     *
     * The student list is copied deeply, the others are not. */
    @Override
    public Object clone() throws CloneNotSupportedException {
        Lecture cpy = (Lecture) super.clone();
        cpy.students = new ArrayList<Student>(students);
        return cpy;
    }

    @Override
    public int hashCode() {
        // Note that if objects are equal then they shall return the same hash
        // code! (But obviously not vice versa.)
        // We would not need to add students to fulfill the contract of
        // Object.equal(). Actually, we may like to remove it to make
        // hashCode() faster and O(1).
        return Objects.hash(title, teacher, students);
    }

    /** Returns true iff given object is equal.
     *
     * The given object is equal iff it is a Lecture with same title, teacher
     * and student list. */
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;

        if (!(o instanceof Lecture))
            return false;

        // So o is a non-identical Lecture.
        Lecture obj = (Lecture) o;

        if (!title.equals(obj.title))
            return false;

        if (teacher != obj.teacher)
            return false;

        // Read specification of ArrayList.equals() here!
        if (!students.equals(obj.students))
            return false;

        return true;
    }

    @Override
    public String toString() {
        return "Lecture " + title +
               " given by " + teacher.getName() + ". Students: " +
               students.toString();
    }
}
