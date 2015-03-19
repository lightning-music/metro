#include <metro/metro.h>
#include <stdio.h>
#include <stdlib.h>

void *
tick(void *arg)
{
    int *count = (int*) arg;
    printf("%d Hi\n", (*count)++);
    return NULL;
}

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
