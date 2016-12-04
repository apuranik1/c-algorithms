#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "sort.h"

int main() {
    int nums[10] = {3,4,2,1,5,7,6,0,9,8};
    int_heapsort(nums, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", nums[i]);
    }

    array* dyn_nums = create_array();
    while (1) {
        int value;
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        array_append(dyn_nums, value);
    }

    return 0;
}

