#include <check.h>

#include "statistics.h"

typedef struct numbers {
    size_t  len;
    double* ptr;
} numbers_t;

static double reference_average(numbers_t numbers)
{
    double sum = 0;

    for (size_t i = 0; i < numbers.len; ++i)
    {
        sum += numbers.ptr[i];
    }

    return sum / ((double) numbers.len);
}

// This cannot be inside a function since the `(double[]){...}` syntax creates
// an array literal with function scope inside a function.
static numbers_t test_cummulative_average_against_reference_implementation_DATA[] = {
    {1, (double[]){42}},
    {5, (double[]){10, 40, 30, 20, 50}},
    {6, (double[]){2, 10, 3, 5, 7, 3}},
};

START_TEST(test_cummulative_average_against_reference_implementation)
{
    numbers_t numbers = test_cummulative_average_against_reference_implementation_DATA[_i];

    double expected_average = reference_average(numbers);
    double actual_average = 0;

    for (size_t i = 0; i < numbers.len; ++i)
    {
        actual_average = cummulative_average(actual_average, numbers.ptr[i], i + 1);
    }

    ck_assert_double_eq(expected_average, actual_average);
}
END_TEST

Suite* create_statistics_suite()
{
    Suite* suite = suite_create("statistics");

    TCase* cummulative_average_tcase = tcase_create("cummulative_average");
    suite_add_tcase(suite, cummulative_average_tcase);

    tcase_add_loop_test(cummulative_average_tcase, test_cummulative_average_against_reference_implementation, 0, 3);

    return suite;
}
