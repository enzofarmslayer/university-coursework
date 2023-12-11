from cal_ui import *

def cd_minus_appointment(cal_day: CalendarDay, time: Time) -> CalendarDay:
    """
    Returns a copy of the given CalendarDay, where the given Appointment
    has been removed.
    """
    ensure_type(time, Time)
    ensure_type(cal_day, CalendarDay)

    new_cal_day_app = cal_day.appointments.copy()

    for app in new_cal_day_app:
        if time == ts_start(app.span):
            new_cal_day_app.remove(app)

    return new_calendar_day(cd_day(cal_day), new_cal_day_app)

def minus_appointment(
    cal_year: CalendarYear,
    day: Day,
    mon: Month,
    time: Time,
) -> CalendarYear:
    """
    Return a new CalendarYear where an appointment, specified by the parameters,
    has been rmeoved in the appropriate CalendarDay.
    """

    old_cal_month = cy_get_month(mon, cal_year)
    old_cal_day = cm_get_day(old_cal_month, day)

    new_cal_day = cd_minus_appointment(old_cal_day, time)
    new_cal_month = cm_plus_cd(old_cal_month, new_cal_day)
    new_cal_year = cy_plus_cm(cal_year, new_cal_month)

    return new_cal_year


def remove(cal_name: str, d: int, m: str, t1: str) -> None:
    """Remove an appointment in the calendar."""
    day = new_day(d)
    mon = new_month(m)
    start = new_time_from_string(t1)
    cal_year = get_calendar(cal_name)
    cal_month = cy_get_month(mon, cal_year)
    cal_day = cm_get_day(cal_month, day)

    if not is_booked_from(cal_day, start):
        print("No appointment exist during the given time.")
    else:
        new_year = minus_appointment(cal_year, day, mon, start)
        insert_calendar(cal_name, new_year)
        print("The appointment has been removed.")

"""
create("enzo")
book("enzo", 30, "nov", "14:00", "16:00", "knas")
book("enzo", 30, "nov", "16:30", "19:00", "mys")
show("enzo", 30, "nov")
remove("enzo", 30, "nov", "14:00")
book("enzo", 30, "nov", "19:30", "20:00", "mys2")
show("enzo", 30, "nov")
"""