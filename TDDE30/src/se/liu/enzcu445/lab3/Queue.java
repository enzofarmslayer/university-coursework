package se.liu.enzcu445.lab3;

import se.liu.enzcu445.lab1.Person;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Queue extends ListManipulator {

    public Queue() {
        super();
    }

    public Person dequeue() {
        if (elements.isEmpty()) {
            return null;
        }
        return elements.remove(0);
    }
}
