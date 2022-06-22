#include <stdlib.h>

#include <check.h>

extern Suite* create_statistics_suite();
extern Suite* create_resources_suite();
extern Suite* create_queue_suite();

int main(void)
{
    SRunner* sr = srunner_create(NULL);
    srunner_add_suite(sr, create_statistics_suite());
    srunner_add_suite(sr, create_resources_suite());
    srunner_add_suite(sr, create_queue_suite());

    srunner_run_all(sr, CK_ENV);
    int tests_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return tests_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
