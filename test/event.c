#include <check.h>
#include <metro/event.h>
#include <stdlib.h>

START_TEST(test_Event_init)
{
    Event e = Event_init();
    ck_assert(e);
}
END_TEST

Suite *
event_suite(void)
{
    Suite *suite;
    TCase *tcase;
    suite = suite_create("Event");
    tcase = tcase_create("Event_init");
    tcase_add_test(tcase, test_Event_init);
    suite_add_tcase(suite, tcase);
    return suite;
}

int
main(void)
{
    int number_failed;
    Suite *suite;
    SRunner *runner;

    suite = event_suite();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
