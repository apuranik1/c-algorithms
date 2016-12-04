#ifndef ALG_ARRAY_H_
#define ALG_ARRAY_H_

typedef struct {
    int* data;
    int size;
    int capacity;
} array;

array* create_array();
void array_append(array* arr, int value);
int array_get(const array* arr, int index);
void array_set(array* arr, int index, int value);

#endif
