#include <metro/metro.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *
tick(void *arg)
{
    int *count = (int*) arg;
    printf("%d Hi\n", (*count)++);
    return NULL;
}

void
show_clock_res(struct timespec t);

int
main(int argc, char **argv)
{
    int rc;
    int count = 0;
    Metro metro = Metro_create(120, tick, &count);

    rc = Metro_start(metro);

    if (rc != 0) {
        return rc;
    }
    rc = Metro_wait(metro);
    if (rc != 0) {
        return rc;
    }
    Metro_free(&metro);
    return 0;
}
