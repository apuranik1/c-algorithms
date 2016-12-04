#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "heap.h"

void mergesort(void* arr, size_t nitems, size_t size, int (*cmp)(const void*, const void*)) {

    if (nitems <= 1) {
        return;
    }

    size_t midpoint = nitems / 2;
    mergesort(arr, midpoint, size, cmp);
    mergesort(arr+midpoint*size, nitems - midpoint, size, cmp);

    /* merge the two sorted lists */
    void* dest = malloc(size * nitems);
    void* current_dest = dest;
    void* pos1 = arr;
    void* middle_p = arr+size*midpoint;
    void* pos2 = middle_p;
    void* end = arr + nitems;
    while (pos1 != middle_p && pos2 != end) {
        int result = cmp(pos1, pos2);
        if (result <= 0) {
            memcpy(current_dest, pos1, size);
            current_dest = (char*)current_dest + size;
            pos1 = (char*)pos1 + size;
        } else {
            memcpy(current_dest, pos2, size);
            current_dest = (char*)current_dest + size;
            pos2 = (char*)pos2 + size;
        }
    }
    /* copy anything we haven't handled yet */
    size_t len1 = (char*)middle_p - (char*)pos1;
    memcpy(current_dest, pos1, len1);
    current_dest = current_dest + len1;

    size_t len2 = (char*)end - (char*)pos2;
    memcpy(current_dest, pos2, len2);
    /* copy back from dest to original array */

    int* copy_pos = arr;
    current_dest = dest;
    memcpy(arr, dest, size * nitems);

    free(dest);
}

void int_mergesort(int* arr, int size) {

    if (size <= 1) {
        return;
    }

    int midpoint = size / 2;
    int_mergesort(arr, midpoint);
    int_mergesort(arr+midpoint, size - midpoint);

    /* merge the two sorted lists */
    int* dest = (int*) malloc(sizeof(int) * size);
    int* current_dest = dest;
    int* pos1 = arr;
    int* middle_p = arr+midpoint;
    int* pos2 = middle_p;
    int* end = arr + size;
    while (pos1 != middle_p && pos2 != end) {
        if (*pos1 <= *pos2) {
            *(current_dest++) = *(pos1++);
        } else {
            *(current_dest++) = *(pos2++);
        }
    }
    /* copy anything we haven't handled yet */
    while (pos1 != middle_p) {
        *(current_dest++) = *(pos1++);
    }
    while (pos2 != end) {
        *(current_dest++) = *(pos2++);
    }
    /* copy back from dest to original array */

    int* copy_pos = arr;
    current_dest = dest;
    while (copy_pos != end) {
        *(copy_pos++) = *(current_dest++);
    }

    free(dest);
}

void int_heapsort(int* arr, int size) {
    int_heapify(arr, size);
    for (int i = size-1; i >= 0; --i)
        arr[i] = int_heappop(arr, i+1);
}

int int_binary_search(int* arr, size_t size)
