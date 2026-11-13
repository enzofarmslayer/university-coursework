package se.liu.enzcu445.lab1;

import java.time.LocalDate;
import java.time.Period;

public class Person {
    private String name;
    private LocalDate birthDay;

    public Person(String name, LocalDate birthDay) {
        this.name = name;
        this.birthDay = birthDay;
    }

    @Override
    public String toString() {
        // When calling print function on a Person the namne and age gets printed instead
        return name + " " + getAge();
    }

    public int getAge() {
        // Calculates and returns a Persons age based on their birthday
        return Period.between(birthDay, LocalDate.now()).getYears();
    }

    public static void main(String[] args){
        // Creates two Person objects and prints them
        LocalDate birthDateEnzo = LocalDate.of(2004,10,18);
        Person enzo = new Person("Enzo", birthDateEnzo);

        LocalDate birthDateIwan = LocalDate.of(1971,1,23);
        Person iwan = new Person("Iwan", birthDateIwan);

        System.out.println(enzo);
        System.out.println(iwan);
    }
}
