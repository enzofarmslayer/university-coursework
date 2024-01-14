package se.liu.enzcu445.calendar;

public class TimeSpan {
    private TimePoint start;
    private TimePoint end;

    public TimeSpan(TimePoint start, TimePoint end) {
        this.start = start;
        this.end = end;
    }

    public TimePoint getStart() {
        return start;
    }

    public TimePoint getEnd() {
        return end;
    }

    @Override
    public String toString() {
        return start.toString() +
                " - " + end.toString();
    }
}
