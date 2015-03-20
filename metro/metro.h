/**
 * \brief Metronome for music applications
 */
#ifndef METRO_H_INCLUDED
#define METRO_H_INCLUDED

#include <stdint.h>

typedef struct Metro *Metro;

typedef float Bpm;

typedef uint64_t Nanoseconds;

typedef void* (*MetroFunc)(void *arg);

/**
 * Create a metro that fires every beat according to bpm.
 * Returns NULL on error.
 */
Metro
Metro_create(Bpm bpm, MetroFunc f, void *data);

/**
 * Start a metro. Returns 0 on success, nonzero on failure.
 */
int
Metro_start(Metro metro);

/**
 * Stop a metro. Returns 0 on success, nonzero on failure.
 */
int
Metro_stop(Metro metro);

/**
 * Change tempo in bpm. Returns the old tempo.
 */
Bpm
Metro_set_bpm(Metro metro, Bpm bpm);

/**
 * Join to the thread running the metro.
 * This causes the calling thread to block forever.
 */
int
Metro_wait(Metro metro);

/**
 * Free the resources held by a metro.
 */
void
Metro_free(Metro *metro);

#endif
