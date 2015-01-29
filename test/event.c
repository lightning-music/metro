#include <check.h>
#include <metro/event.h>
#include <metro/thread.h>
#include <stdlib.h>
#include <unistd.h>

START_TEST(test_Event_init)
{
    Event e = Event_init();
    ck_assert(e);
    Event_free(&e);
}
END_TEST

START_TEST(test_Event_wait)
{
    Event e = Event_init();
    ck_assert(e);
    
    Event_free(&e);
}
END_TEST

Suite *
event_suite(void)
{
    Suite *suite;
    TCase *tcase_init;
    TCase *tcase_wait;
    suite = suite_create("Event");

    tcase_init = tcase_create("Event_init");
    tcase_add_test(tcase_init, test_Event_init);

    tcase_wait = tcase_create("Event_wait");
    tcase_add_test(tcase_wait, test_Event_wait);

    suite_add_tcase(suite, tcase_init);
    suite_add_tcase(suite, tcase_wait);

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
