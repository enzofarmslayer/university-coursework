package se.liu.enzcu445.lab3;

import se.liu.enzcu445.lab1.Person;

import java.time.LocalDate;

public class TestQS {
    public static void main(String[] args) {
        LocalDate birthDateEnzo = LocalDate.of(2004, 10, 18);
        Person enzo = new Person("Enzo", birthDateEnzo);

        LocalDate birthDateIwan = LocalDate.of(1971, 1, 23);
        Person iwan = new Person("Iwan", birthDateIwan);

        LocalDate birthDateVera = LocalDate.of(1971, 1, 23);
        Person vera = new Person("Vera", birthDateVera);

        Stack stack = new Stack();
        stack.push(enzo);
        stack.push(iwan);
        stack.push(vera);

        System.out.println("Stack:");
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }

        Queue queue = new Queue();
        queue.enqueue(enzo);
        queue.enqueue(iwan);
        queue.enqueue(vera);

        System.out.println("\nQueue:");
        while (!queue.isEmpty()) {
            System.out.println(queue.dequeue());
        }
    }
}
