# Write your code for lab 8d here.
from cal_abstraction import CalendarDay, Time
from settings import CHECK_AGAINST_FACIT
from cal_ui import *
from lab8c import *

if CHECK_AGAINST_FACIT:
    try:
        from facit_la8_uppg import TimeSpanSeq
    except:
        print("*" * 100)
        print("*" * 100)
        print("Kan inte hitta facit; ändra CHECK_AGAINST_FACIT i test_driver.py till False")
        print("*" * 100)
        print("*" * 100)
        raise
else:
    from lab8b import *


def time_is_in_span(t: Time, ts: TimeSpan) -> bool:
    """Check if the given time is within the provided timespan."""
    start = ts_start(ts)
    end = ts_end(ts)

    return time_precedes_or_equals(start, t) and time_precedes(t, end)


def first_free_time(start, end, apps) -> Time:
    """Find the first available time."""
    first_time = None
    in_time_span = False
    for app in apps:
        if first_time:
            if time_is_in_span(first_time, app.span):
                first_time = None

        if time_is_in_span(start, app.span):
            in_time_span = True
            if time_precedes(end, ts_end(app.span)):
                continue
            if not first_time:
                first_time = ts_end(app.span)

    if not first_time and in_time_span:
        return None
    elif not first_time:
        return start
    else:
        return first_time


def first_busy_time(start, end, apps) -> Time:
    """Find the first non-available time."""
    first_busy_time = None
    for app in apps:
        app_start = ts_start(app.span)
        if time_precedes(start, app_start) and time_precedes(app_start, end):
            first_busy_time = ts_start(app.span)
            break

    return first_busy_time


def free_spans(cal_day: CalendarDay, start: Time, end: Time) -> TimeSpanSeq:
    """Return all timespans that are not booked in the time interval of the given day."""
    apps = []
    for app in cd_iter_appointments(cal_day):
        apps.append(app)
    tss_spans = new_time_span_seq()

    # Check if there are no appointments
    if not apps:
        return tss_plus_span(tss_spans, new_time_span(start, end))

    # Find first available time given span
    first_time = first_free_time(start, end, apps)
    if not first_time:
        return tss_spans

    # Find end time of first free span
    end_time = first_busy_time(start, end, apps)

    if end_time:
        # Check for more free spans
        tss_spans = free_spans(cal_day, end_time, end)
    else:
        # This was the last free span in the time interval
        end_time = end

    # Add free span to sequence
    if first_time != end_time:
        free_span = new_time_span(first_time, end_time)
        tss_spans = tss_plus_span(tss_spans, free_span)

    return tss_spans

def show_free(cal_name: str, d: int, m: str, t1: str, t2: str):
    day = new_day(d)
    mon = new_month(m)
    start = new_time_from_string(t1)
    end = new_time_from_string(t2)
    cal_year = get_calendar(cal_name)
    cal_month = cy_get_month(mon, cal_year)
    cal_day = cm_get_day(cal_month, day)
    
    tss = free_spans(cal_day, start, end)
    show_time_spans(tss)

"""
# Example
create("Lukas")
book("Lukas", 13, "dec", "12:00", "13:00", "Lucia")
book("Lukas", 13, "dec", "17:00", "18:30", "Handla mat")
show_free("Lukas", 13, "dec", "09:00", "20:00")
"""