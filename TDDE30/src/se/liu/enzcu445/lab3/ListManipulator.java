package se.liu.enzcu445.lab3;

import se.liu.enzcu445.lab1.Person;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ListManipulator {
    protected List<Person> elements;

    public ListManipulator() {
        elements = new ArrayList<>();
    }

    public int size() {
        return elements.size();
    }

    public boolean isEmpty() {
        return elements.isEmpty();
    }

    public boolean contains(Object o) {
        return elements.contains(o);
    }

    public Iterator<Person> iterator() {
        return elements.iterator();
    }

    public boolean add(Person person) {
        return elements.add(person);
    }

    public boolean remove(Object o) {
        return elements.remove(o);
    }

    public void clear() {
        elements.clear();
    }

    public void enqueue(Person person) {
        elements.add(person);
    }
}
