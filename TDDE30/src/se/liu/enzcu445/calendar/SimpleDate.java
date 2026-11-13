package se.liu.enzcu445.calendar;

public class SimpleDate {
    private int year;
    private Month month;
    private int day;

    public SimpleDate(int year, Month month, int day) {
        this.year = year;
        this.month = month;
        this.day = day;
    }

    public int getYear() {
        return year;
    }

    public Month getMonth() {
        return month;
    }

    public int getDay() {
        return day;
    }

    @Override
    public String toString() {
        return getDay() +
                "/" + month.getNumber() +
                " - " + getYear();
    }
}
