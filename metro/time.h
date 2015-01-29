#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <stdint.h>

typedef struct Time *Time;

Time
Time_now();

Time
Time_init(uint64_t seconds, uint64_t useconds);

int
Time_usleep(uint32_t interval);

void
Time_free(Time *time);

#endif
