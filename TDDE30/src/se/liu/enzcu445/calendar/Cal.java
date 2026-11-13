package se.liu.enzcu445.calendar;

import java.util.ArrayList;
import java.util.List;

public class Cal {
    private List<Appointment> appointments;

    public Cal(List<Appointment> appointments) {
        this.appointments = new ArrayList<>();
    }

    public void show(){
        for (Appointment appointment: appointments ) {
            System.out.println(appointment +"\n------------------------------");
        }
    }

    public void book(int year, String month, int day,
                     int startHour, int startMinute, int endHour,
                     int endMinute, String subject){

        if (year <= 1970 ||
                startHour < 0 || startHour > 23 ||
                endHour < 0 || endHour > 23 ||
                startMinute < 0 || startMinute > 59 ||
                endMinute < 0 || endMinute > 59) {
            throw new IllegalArgumentException("Invalid date or time parameters");
        }

        Month monthFull = new Month(month, Month.getMonthNumber(month), Month.getMonthDays(month));
        if (day < 1 || day > monthFull.getDays()) {
            throw new IllegalArgumentException("Invalid day for the given month");
        }

        SimpleDate date = new SimpleDate(year, monthFull, day);
        TimePoint startTime = new TimePoint(startHour, startMinute);
        TimePoint endTime = new TimePoint(endHour, endMinute);
        TimeSpan timeSpan = new TimeSpan(startTime, endTime);

        Appointment newAppointment = new Appointment(subject, date, timeSpan);

        appointments.add(newAppointment);
    }
}
