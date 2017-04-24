#include <stdlib.h>
#include <limits.h>

#include "intervals.h"
#include "sort.h"

typedef struct {
    alg_interval inter;
    int index;
} indexed_interval;


typedef struct {
    alg_weighted_interval inter;
    int index;
} indexed_weighted_interval;


int inter_cmp_by_start(const void *first, const void *second) {
    return ((alg_interval *)first)->start - ((alg_interval *)second)->start;
}


int inter_cmp_by_end(const void *first, const void *second) {
    return ((alg_interval *)first)->end - ((alg_interval *)second)->end;
}


/*
 * Schedule as many intervals as possible without overlaps.
 * Return an array of booleans
 */
int * schedule_intervals(alg_interval *intervals, size_t nitems) {
    indexed_interval *i_inters = malloc(sizeof(indexed_interval) * nitems);
    for (size_t i = 0; i < nitems; ++i) {
        i_inters[i].inter = intervals[i];
        i_inters[i].index = i;
    }
    mergesort(i_inters, nitems, sizeof(i_inters), &inter_cmp_by_end);
    int *inter_flags = calloc(nitems, sizeof(int));
    int last_used = INT_MIN;
    for (size_t i = 0; i < nitems; ++i) {
        if (i_inters[i].inter.start >= last_used) {
            last_used = i_inters[i].inter.end;
            inter_flags[i_inters[i].index] = 1;
        }
    }
    free(i_inters);
    return inter_flags;
}


int * schedule_weighted_intervals(alg_weighted_interval *intervals, size_t nitems) {
    /* Algorithm: sorted <-- sort intervals by end time, tracking original index
     *
     * create array bestbefore - tracks best result that uses intervals ending
     * before sorted[i] starts
     * also create array prev - tracks previous used interval
     *
     * at each step: you either take the current interval (which ends here) and
     * use it together with bestbefore[find start position]
     * or you just copy over position n-1
     */
    indexed_weighted_interval *i_inters = malloc(sizeof(indexed_weighted_interval) * nitems);
    for (int i = 0; i < nitems; ++i) {
        i_inters[i].inter = intervals[i];
        i_inters[i].index = i;
    }

    /* store the best result using intervals ending before sorted[i] starts */
    int *bestbefore = malloc(nitems * sizeof(int));
    /* store the previous interval used */
    int *prev = malloc(nitems * sizeof(int));
    mergesort(i_inters, nitems, sizeof(indexed_weighted_interval), &inter_cmp_by_end);

    for (size_t current = 0; current < nitems; ++current) {
        /* find optimum for current slot */
        int bestWith = i_inters[current].inter.weight;
        /* interval which ends when the current interval starts - looking for the boundary */
        alg_interval marker = {.start = 0, .end = i_inters[current].inter.interval.end};
        indexed_weighted_interval* lastEligible = binary_search(
                &marker, i_inters, nitems, sizeof(alg_weighted_interval),
                &inter_cmp_by_end
        );
        if (lastEligible != i_inters || intervals[0].interval.end <= marker.end) {
            /* Legal previous interval found */
        }
    }
}
