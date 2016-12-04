#ifndef ALG_SORT_H_
#define ALG_SORT_H_

#include <stdlib.h>

void mergesort(void* arr, size_t nitems, size_t width, int (*cmp)(const void*, const void*));
void int_mergesort(int* arr, int size);
void int_heapsort(int* arr, int size);

#endif
