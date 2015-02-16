#include "metro/mem.h"
#include "metro/metro.h"

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#define TIMER_CREATE_SUCCESS 0

static void
timer_tick(union sigval arg);

struct Metro {
    timer_t *tid;
};

Metro
Metro_create()
{
    Metro metro;
    NEW(metro);

    struct sigevent tick;
    tick.sigev_notify = SIGEV_THREAD;
    tick.sigev_value.sival_ptr = NULL;
    tick.sigev_notify_function = timer_tick;
    
    timer_t tid;
    int rc = timer_create(CLOCK_REALTIME, &tick, &tid);

    if (rc != TIMER_CREATE_SUCCESS) {
        return NULL;
    }
    
    return metro;
}

void
Metro_free(Metro *metro)
{
}

static void
timer_tick(union sigval arg)
{
}
