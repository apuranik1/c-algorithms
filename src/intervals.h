#ifndef ALG_INTERVALS_H_
#define ALG_INTERVALS_H_

#include <stdlib.h>

typedef struct {
    int start;
    int end;
} alg_interval;

typedef struct {
    alg_interval interval;
    int weight;
} alg_weighted_interval;

int* schedule_intervals(alg_interval* intervals, size_t nitems);

int* schedule_weighted_intervals(alg_weighted_interval* intervals, size_t nitems);

#endif
