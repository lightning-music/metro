#include "mem.h"
#include "metro.h"

struct Metro {
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
