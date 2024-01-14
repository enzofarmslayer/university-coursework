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
    public int getAge() {
        return Period.between(birthDay, LocalDate.now()).getYears();
    }

    @Override
    public String toString() {
        return name + " " + getAge();
    }

    public static void main(String[] args){
        LocalDate birthDateEnzo = LocalDate.of(2004,10,18);
        Person Enzo = new Person("Enzo", birthDateEnzo);

        LocalDate birthDateIwan = LocalDate.of(1971,1,23);
        Person Iwan = new Person("Iwan", birthDateIwan);

        System.out.println(Enzo);
        System.out.println(Iwan);
    }
}
