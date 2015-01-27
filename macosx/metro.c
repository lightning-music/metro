#include "mem.h"
#include "metro.h"

#include <stddef.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#define KQUEUE_ERROR -1

typedef int timer_t;

struct Metro {
    timer_t tid;
};

Metro
Metro_create()
{
    Metro metro;
    NEW(metro);

    timer_t timer = kqueue();
    if (KQUEUE_ERROR == timer) {
        return NULL;
    }
    metro->tid = timer;

    return metro;
}

void
Metro_free(Metro *metro)
{
}
