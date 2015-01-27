#include "mem.h"
#include "metro.h"

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

struct Metro {
    timer_t *tid;
};

Metro
Metro_create()
{
    Metro metro;
    NEW(metro);
    return metro;
}

void
Metro_free(Metro *metro)
{
}
