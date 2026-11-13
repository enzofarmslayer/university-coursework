package se.liu.enzcu445.calendar;

import java.util.ArrayList;
import java.util.List;

public class TestCal
{
        public static void main(String[] args) {
            List<Appointment> appointments1 = new ArrayList<>();

            Cal calendar = new Cal(appointments1);

            calendar.book(2023, "january", 5, 14, 30, 15, 30, "Enzo");
            calendar.book(2023, "february", 12, 10, 0, 11, 0, "Iwan");
            calendar.book(2023, "march", 22, 9, 30, 10, 30, "Vera");
            calendar.book(2023, "april", 15, 16, 0, 17, 0, "Naomi");

            calendar.show();
        }
}
