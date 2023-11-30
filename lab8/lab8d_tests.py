# Write your code for lab 8d here.

from test_driver import store_test_case, run_free_spans_tests


# Create additional test cases, and add to them to create_tests_for_free_span().

def create_tests_for_free_span() -> dict:
    """Create and return a number of test cases for the free_spans function"""
    test_cases = dict()

    store_test_case(
        test_cases,
        1,
        start_str="08:00",  # Search interval starts
        end_str="21:00",  # Search interval ends
        booking_data=["07:00-09:00", "13:00-18:00"],  # This day's appointments
        exp_result=["09:00-13:00", "18:00-21:00"],
    )  # Expected free time

    store_test_case(
        test_cases,
        2,
        start_str="08:00",  # Search interval starts
        end_str="22:00",  # Search interval ends
        booking_data=["07:00-09:00", "09:00-13:00", "13:00-23:00"],  # This day's appointments
        exp_result=[],
    )  # Expected no free time

    store_test_case(
        test_cases,
        3,
        start_str="07:00",  # Search interval starts
        end_str="21:00",  # Search interval ends
        booking_data=[],  # This day's appointments
        exp_result=["07:00-21:00"],
    )  # No booked times

    store_test_case(
        test_cases,
        4,
        start_str="07:00",  # Search interval starts
        end_str="16:00",  # Search interval ends
        booking_data=["09:00-10:30", "15:00-18:00"],  # This day's appointments
        exp_result=["07:00-09:00", "10:30-15:00"],
    )  # Cut off result at end of search time

    store_test_case(
        test_cases,
        5,
        start_str="15:00",  # Search interval starts
        end_str="08:00",  # Search interval ends
        booking_data=["09:00-10:30", "16:00-18:00"],  # This day's appointments
        exp_result=[],
    )  # Search start is after end

    store_test_case(
        test_cases,
        6,
        start_str="07:00",  # Search interval starts
        end_str="07:00",  # Search interval ends
        booking_data=["09:00-10:30"],  # This day's appointments
        exp_result=[],
    )  # Start and end is the same

    print("Test cases generated.")

    return test_cases


if __name__ == '__main__':
    # Actually run the tests, using the test driver functions
    tests = create_tests_for_free_span()
    run_free_spans_tests(tests)
