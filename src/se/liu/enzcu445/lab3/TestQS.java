package se.liu.enzcu445.lab3;

import se.liu.enzcu445.lab1.Person;

import java.time.LocalDate;

public class TestQS {
    public static void main(String[] args) {
        LocalDate birthDateEnzo = LocalDate.of(2004, 10, 18);
        Person Enzo = new Person("Enzo", birthDateEnzo);

        LocalDate birthDateIwan = LocalDate.of(1971, 1, 23);
        Person Iwan = new Person("Iwan", birthDateIwan);

        LocalDate birthDateVera = LocalDate.of(1971, 1, 23);
        Person Vera = new Person("Vera", birthDateVera);

        Stack stack = new Stack();
        stack.push(Enzo);
        stack.push(Iwan);
        stack.push(Vera);

        System.out.println("Stack:");
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }

        Queue queue = new Queue();
        queue.enqueue(Enzo);
        queue.enqueue(Iwan);
        queue.enqueue(Vera);

        System.out.println("\nQueue:");
        while (!queue.isEmpty()) {
            System.out.println(queue.dequeue());
        }
    }
}
