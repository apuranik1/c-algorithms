#include <stdlib.h>
#include <assert.h>

#include "array.h"

array* create_array() {
    int INITIAL_SIZE = 10;
    array* new_array = malloc(sizeof(array));
    new_array->capacity = INITIAL_SIZE;
    new_array->size = 0;
    new_array->data = malloc(sizeof(int) * INITIAL_SIZE);
    return new_array;
}

void array_resize(array* arr, int new_capacity) {
    arr->data = realloc(arr->data, sizeof(int) * new_capacity);
}

int array_get(const array* arr, int index) {
    assert(0 <= index);
    assert(index < arr->size);
    return arr->data[index];
}

void array_set(array* arr, int index, int value) {
    assert(0 <= index);
    assert(index < arr->size);
    arr->data[index] = value;
}

void array_append(array* arr, int value) {
    if (arr->size >= arr->capacity) {
        /* expand array */
        array_resize(arr, arr->capacity*2+1);
    }
    ++arr->size;
    array_set(arr, arr->size-1, value);
}
