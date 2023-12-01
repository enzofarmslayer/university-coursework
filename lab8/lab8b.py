from typing import NamedTuple, List
from cal_abstraction import *
# =========================================================================
# Type definition
# =========================================================================

# Define the type somehow...  The initial "" is simply here as a placeholder.
TimeSpanSeq = NamedTuple("TimeSpanSeq", [("Timespans", List[TimeSpan])])
# =========================================================================
#  Function implementations
# =========================================================================

# Implement these functions!  Also determine if you need *additional* functions.

def new_time_span_seq(timespans: List[TimeSpan] = None):

    def add_span(seq: List[TimeSpan], span):
        span_start_t = ts_start(span)
        span_start_t_num = span_start_t.hour.number * 60 + span_start_t.minute.number

        if not seq: return [span]
        new_seq = seq.copy()

        i = 0
        for ts in new_seq:
            start_t = ts_start(ts)
            time_num = start_t.hour.number * 60 + start_t.minute.number
            if time_num > span_start_t_num: break
            i += 1
        
        new_seq.insert(i, span)
        return new_seq

    new_tss = TimeSpanSeq([])
    if timespans:
        for ts in timespans:
            new_tss = TimeSpanSeq(add_span(new_tss.Timespans, ts))

    return new_tss


def tss_is_empty(tss):
    ensure_type(tss, TimeSpanSeq)
    if tss.Timespans: return False
    return True


def tss_plus_span(tss, ts):
    ensure_type(tss, TimeSpanSeq)
    ensure_type(ts, TimeSpan)

    if tss.Timespans:
        new_seq = tss.Timespans.copy()
    else:
        new_seq = []
    new_seq.append(ts)

    return new_time_span_seq(new_seq)

def tss_iter_spans(tss):
    ensure_type(tss, TimeSpanSeq)
    for ts in tss.Timespans:
        yield ts


def show_time_spans(tss):
    ensure_type(tss, TimeSpanSeq)
    i = 1
    if tss.Timespans: 
        for ts in tss.Timespans:
            print("Timespan " + str(i) + " |  " + "Start: " + str(ts_start(ts).hour.number) + "h " + str(ts_start(ts).minute.number) + "min \t" + "End: " + str(ts_end(ts).hour.number) + "h " + str(ts_end(ts).minute.number) + str("min"))
            i += 1
    else:
        print("Timespan sequence is empty")


# Keep only time spans that satisfy pred.
# You do not need to modify this function.
def tss_keep_spans(tss, pred):
    result = new_time_span_seq()
    for span in tss_iter_spans(tss):
        if pred(span):
            result = tss_plus_span(result, span)

    return result


m8 = new_minute(8)
m14 = new_minute(14)
m25 = new_minute(25)
m49 = new_minute(49)

h0 = new_hour(0)
h2 = new_hour(2)
h4 = new_hour(4)
h6 = new_hour(6)

t1 = new_time(h0, m8)
t2 = new_time(h2, m14)
t3 = new_time(h4, m25)
t4 = new_time(h6, m49)

ts1 = new_time_span(t1, t2)
ts2 = new_time_span(t3, t4)
ts3 = new_time_span(t1, t3)

tss = new_time_span_seq([ts1, ts2])
tss2 = tss_plus_span(tss, ts3)

#show_time_spans(tss2)