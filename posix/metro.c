#include "metro/event.h"
#include "metro/mem.h"
#include "metro/metro.h"
#include "metro/thread.h"

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CLOCK_TYPE CLOCK_MONOTONIC
#define NS_MAX 999999999
#define SCLASS SchedulingClassRealtime

extern int errno;

struct Metro {
    Thread thread;
    MetroFunc f;
    void *data;
    Bpm bpm;
    Event start;
    Event ready;
    char *strerr;
    volatile int go;
    // clock resolution
    struct timespec res;
};

static void *
Metro_go(void *arg);

static Nanoseconds
bpm_to_nanos(Bpm bpm);

Metro
Metro_create(Bpm bpm, MetroFunc f, void *data)
{
    Metro metro;
    NEW(metro);

    metro->bpm = bpm;
    metro->f = f;
    metro->data = data;
    metro->start = Event_init();
    metro->ready = Event_init();
    metro->thread = Thread_create(Metro_go, metro);

    if (0 != Thread_set_scheduling_class(metro->thread, SCLASS)) {
        return NULL;
    }

    Event_wait(metro->ready);

    return metro;
}

int
Metro_start(Metro metro)
{
    assert(metro);
    assert(__sync_bool_compare_and_swap(&metro->go, metro->go, 1));
    /* metro->thread = Thread_create(Metro_go, metro); */
    /* return 0; */
    return Event_broadcast(metro->start, NULL);
}

int
Metro_stop(Metro metro)
{
    assert(metro);
    return !__sync_bool_compare_and_swap(&metro->go, metro->go, 0);
}

Bpm
Metro_set_bpm(Metro metro, Bpm bpm)
{
    assert(metro);
    Bpm old = metro->bpm;
    metro->bpm = bpm;
    return old;
}

int
Metro_wait(Metro metro)
{
    assert(metro);
    return Thread_join(metro->thread);
}

void
Metro_free(Metro *metro)
{
    assert(metro && *metro);
    // TODO: free members
    FREE(*metro);
}

static void *
Metro_go(void *arg)
{
    Metro metro = (Metro) arg;
    int rc;
    struct timespec wait;
    struct timespec rem;

    Event_signal(metro->ready, NULL);
    
    while (1) {
        Event_wait(metro->start);

        while (metro->go) {
            metro->f(metro->data);
            // what if the sum is greater than 1 sec?
            // should it be computed modulo 1B and add 1 to tv_sec?
            wait.tv_sec = 0;
            wait.tv_nsec = bpm_to_nanos(metro->bpm);
            if (wait.tv_nsec > NS_MAX) {
                metro->strerr = "wait time exceeds max";
                goto exit_main_loop;
                break;
            }
            rc = clock_nanosleep(CLOCK_TYPE, 0, &wait, &rem);
            if (0 != rc) {
                /* metro->strerr = sprintf("%d %s", errno, strerror(errno)); */
                goto exit_main_loop;
                break;
            }
        }
    }

 exit_main_loop:
    return NULL;
}

static Nanoseconds
bpm_to_nanos(Bpm bpm)
{
    static const uint64_t NANOS_PER_MILLI = 1000000ULL;
    // bpm to nanos
    return (Nanoseconds) (((float)60000 / bpm) * NANOS_PER_MILLI);
}
