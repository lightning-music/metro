#define _XOPEN_SOURCE 500 // usleep(linux)

#include <assert.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>

#include "metro/mem.h"
#include "metro/time.h"

struct Time {
    uint64_t seconds;
    uint64_t useconds;
};

Time
Time_now()
{
    Time t;
    NEW(t);
    struct timeval tv;

    assert(0 == gettimeofday(&tv, NULL));

    t->seconds = tv.tv_sec;
    t->useconds = tv.tv_usec;

    return t;
}

Time
Time_init(uint64_t seconds, uint64_t useconds)
{
    Time t;
    NEW(t);
    t->seconds = seconds;
    t->useconds = useconds;
    return t;
}

int
Time_usleep(uint32_t interval)
{
    return usleep(interval);
}

void
Time_free(Time *time)
{
    assert(time && *time);
    FREE(*time);
}
