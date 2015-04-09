// +build cgo
#include "event.h"
#include "mem.h"
#include "metro.h"
#include "thread.h"

#include <assert.h>
#include <libkern/OSAtomic.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <stddef.h>
#include <stdio.h>

struct Metro {
    Thread thread;
    Bpm bpm;
    Event start;
    Event ready;
    Event tick;
    volatile int go;
};

void *
Metro_go(void *arg);

static uint64_t
bpm_to_abs(mach_timebase_info_data_t ti, Bpm bpm);

Metro
Metro_create(Bpm bpm)
{
    Metro metro;
    NEW(metro);

    metro->bpm = bpm;
    metro->go = 0;
    metro->start = Event_init();
    metro->ready = Event_init();
    metro->tick = Event_init();
    // start the metro
    metro->thread = Thread_create(Metro_go, metro);
    if (0 != Thread_set_scheduling_class(metro->thread, SchedulingClassRealtime)) {
        return NULL;
    }

    return metro;
}

int
Metro_start(Metro metro)
{
    assert(metro);
    metro->go = 1;
    return Event_signal(metro->start, NULL);
}

int
Metro_stop(Metro metro)
{
    assert(metro);
    // cas returns true if the operation succeeded,
    // which we want to invert to return 0 if the operation
    // succeeds
    return !OSAtomicCompareAndSwapInt(metro->go, 0, &metro->go);
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

Event
Metro_tick(Metro metro)
{
    assert(metro);
    return metro->tick;
}

void
Metro_free(Metro *metro)
{
    assert(metro && *metro);
    Thread_free(&(*metro)->thread);
    Event_free(&(*metro)->start);
    Event_free(&(*metro)->ready);
    Event_free(&(*metro)->tick);
    FREE(*metro);
}

void *
Metro_go(void *arg)
{
    Metro metro = (Metro) arg;

    mach_timebase_info_data_t ti;
    mach_timebase_info(&ti);

    uint64_t now, wait;

    // main loop
    while (1) {
        Event_wait(metro->start);

        while (metro->go) {
            now = mach_absolute_time();
            wait = bpm_to_abs(ti, metro->bpm);
            mach_wait_until(now + wait);
            /* metro->f(metro->data); */
            Event_broadcast(metro->tick, NULL);
        }
    }

    return NULL;
}
 
static uint64_t
bpm_to_abs(mach_timebase_info_data_t ti, Bpm bpm)
{
    static const uint64_t NANOS_PER_MILLI = 1000000ULL;
    // bpm to nanos
    return ((float)60000 / bpm) * NANOS_PER_MILLI * (ti.denom / ti.numer);
}
