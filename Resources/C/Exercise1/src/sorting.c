#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorting.h"
#include "orderedArray.h"

//It searches the index where the element should be inserted
//It accepts as input a pointer to an array, the range between
// it has to find the index defined by low and high and
// a pointer to the element
//It returns the index
//The input parameters cannot be NULL or out of bounds of the
//array
static size_t binarySearch(OrderedArray *ordered_array, size_t low, size_t high, void *item);

static size_t binarySearch(OrderedArray *ordered_array, size_t low, size_t high, void *item) {
    size_t mid;

    if (low == high)
        return low;

    mid = low + ((high - low) / 2);

    if ((*(ordered_array->precedes))((ordered_array->array)[mid], item))
        return binarySearch(ordered_array, mid + 1, high, item);

    if ((*(ordered_array->precedes))(item, (ordered_array->array)[mid]))
        return binarySearch(ordered_array, low, mid, item);

    return mid;
}

static void recursiveInsertionSort(OrderedArray *ordered_array, size_t high) {
    size_t index = 0, i = 0;
    void *tmp;

    for (i = 1; i <= high; i++) {
        tmp = (ordered_array->array)[i];
        index = binarySearch(ordered_array, 0, i, tmp);

        if (index > high) {
            fprintf(stderr, "insertion_sort: index out of bounds of the array");
            exit(EXIT_FAILURE);
        }

        if (index < i) {
            memmove((ordered_array->array) + index + 1, (ordered_array->array) + index, sizeof(void *) * (i - index));
            (ordered_array->array)[index] = tmp;
        }
    }
}

void insertionSort(OrderedArray *ordered_array) {
    recursiveInsertionSort(ordered_array, ordered_array->el_num - 1);
}
