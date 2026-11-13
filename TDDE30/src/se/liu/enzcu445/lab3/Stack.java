package se.liu.enzcu445.lab3;

import se.liu.enzcu445.lab1.Person;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Stack extends ListManipulator {

    public Stack() {
        super();
    }

    public void push(Person person) {
        elements.add(person);
    }

    public Person pop() {
        if (elements.isEmpty()) {
            return null;
        }
        return elements.remove(elements.size()-1);
    }
}
