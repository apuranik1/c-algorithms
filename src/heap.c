#include "stdlib.h"
#include "assert.h"

#include "heap.h"

/* implementation of a max-heap */

/* 
 * Push an element down through the heap until it and its children satisfy the
 * heap property
 */
void int_push_down(int* heap, int index, int size) {
    /* children of index i are 2*i+1 and 2*i + 2 */
    int value = heap[index];
    int current_index = index;
    /* midpoint is the first element without two children */
    int midpoint = (size-1)/2;
    /* push current_index down a level until it satisfies heap property */
    while (current_index < midpoint) {
        int child1 = 2*current_index + 1;
        int child2 = child1 + 1;
        int max_child = (heap[child1] >= heap[child2]) ? child1 : child2;

        if (heap[max_child] <= value) {
            /* heap property is satisfied here */
            return;
        }

        /* swap max_child and current_index, set current_index to value */
        heap[current_index] = heap[max_child];
        heap[max_child] = value;
        current_index = max_child;
    }

    /* if size is even and current_index == midpoint, then it has one child */
    if (size % 2 == 0 && current_index == midpoint) {
        int child = size-1;
        if (heap[child] > value) {
            heap[current_index] = heap[child];
            heap[child] = value;
        }
    }
}

/*
 * Push an element up through the heap until it is greater than its children.
 * Assumes the rest of the heap is valid.
 */
void int_push_up(int* heap, int index, int size) {
    assert(index < size);
    int value = heap[index];
    /* push an element up a level until it satisfies heap property */
    while (index != 0) {
        int parent = (index-1)/2;
        if (heap[parent] >= heap[index]) {
            return;
        }
        heap[index] = heap[parent];
        heap[parent] = value;
        index = parent;
    }
}

/*
 * Pop and return the minimum element of heap
 */
int int_heappop(int* heap, int size) {
    assert(size > 0);
    int max_elem = *heap;
    /* place end element at the beginning and push down */
    *heap = *(heap + size - 1);
    int_push_down(heap, 0, size-1);
    return max_elem;
}

/*
 * Push a new element into heap
 */
void int_heappush(int* heap, int element, int size) {
    heap[size] = element;
    int_push_up(heap, size, size+1);
}

/*
 * Create a max-heap from an array
 */
void int_heapify(int* arr, int size) {
    int midpoint = (size-1)/2;
    for (int i = midpoint; i >= 0; --i)
        int_push_down(arr, i, size);
}
