package se.liu.enzcu445.calendar;

import java.util.Map;

public class Month {
    private String name;
    private int number;
    private int days;

    final private static Map<String,Integer> MONTH_NAME_TO_LENGTH = Map.ofEntries(
            Map.entry("january", 31),
            Map.entry("february", 28),
            Map.entry("march", 31),
            Map.entry("april", 30),
            Map.entry("may", 31),
            Map.entry("june", 30),
            Map.entry("july", 31),
            Map.entry("august", 31),
            Map.entry("september", 30),
            Map.entry("october", 31),
            Map.entry("november", 30),
            Map.entry("december", 31)
    );
    final private static Map<String,Integer> MONTH_NAME_TO_NUMBER = Map.ofEntries(
            Map.entry("january", 1),
            Map.entry("february", 2),
            Map.entry("march", 3),
            Map.entry("april", 4),
            Map.entry("may", 5),
            Map.entry("june", 6),
            Map.entry("july", 7),
            Map.entry("august", 8),
            Map.entry("september", 9),
            Map.entry("october", 10),
            Map.entry("november", 11),
            Map.entry("december", 12)
    );


    public Month(String name, int number, int days) {
        this.name = name;
        this.number = number;
        this.days = days;
    }

    public String getName() {
        return name;
    }

    public int getNumber() {
        return number;
    }

    public int getDays() {
        return days;
    }

    public static int getMonthNumber(String name){
        return MONTH_NAME_TO_NUMBER.getOrDefault(name, -1);
    }

    public static int getMonthDays(String name){
        return MONTH_NAME_TO_LENGTH.getOrDefault(name, -1);
    }
}
