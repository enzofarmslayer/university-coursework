package se.liu.enzcu445.calendar;

public class Appointment {
private String subject;
private SimpleDate date;
private TimeSpan timeSpan;

    public Appointment(String subject, SimpleDate date, TimeSpan timeSpan) {
        this.subject = subject;
        this.date = date;
        this.timeSpan = timeSpan;
    }

    public String getSubject() {
        return subject;
    }

    public SimpleDate getDate() {
        return date;
    }

    public TimeSpan getTimeSpan() {
        return timeSpan;
    }

    @Override
    public String toString() {
        return "Subject: " + subject + "\nDate: " + date + "\nTime: " + timeSpan;
    }
}
