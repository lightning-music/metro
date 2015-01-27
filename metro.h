/**
 * \brief metronome for music applications
 */
#ifndef METRO_H_INCLUDED
#define METRO_H_INCLUDED

typedef struct Metro *Metro;

Metro
Metro_create();

void
Metro_free(Metro *metro);

#endif