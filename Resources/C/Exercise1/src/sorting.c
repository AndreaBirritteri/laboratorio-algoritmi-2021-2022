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

struct record {
    int int_id;
    char *string_field1;
    int int_field2;
    float float_field3;
};

void swap(OrderedArray *ordered_array, size_t i, size_t j) {
  void *temp = ordered_array->array[i];
  ordered_array->array[i] = ordered_array->array[j];
  ordered_array->array[j] = temp;
}

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

// function to find the partition position
size_t partition(OrderedArray *ordered_array, size_t low, size_t high) {

  // select the rightmost element as pivot
  void *pivot = ordered_array_get(ordered_array, high);

  // pointer for greater element
  size_t i = (low - 1 + 1);

  // traverse each element of the array
  // compare them with the pivot
  for (size_t j = low; j < high; j++) {
    if ((*(ordered_array->precedes))(ordered_array_get(ordered_array, j), pivot)) {
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;

      // swap element at i with element at j
      swap(ordered_array, i - 1, j);
    }
  }

  // swap the pivot element with the greater element at i
  swap(ordered_array, i + 1 - 1, high);

  // return the partition point
  return (i + 1 - 1);
}

void quickSortRecursive(OrderedArray *ordered_array, size_t low, size_t high) {
  if ((ssize_t)low < (ssize_t)high) {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    size_t pi = partition(ordered_array, low, high);

    // recursive call on the left of pivot
    quickSortRecursive(ordered_array, low, pi - 1);//check overflow

    // recursive call on the right of pivot
    quickSortRecursive(ordered_array, pi + 1, high);
  }
}

void quickSort(OrderedArray *ordered_array) {
  quickSortRecursive(ordered_array, 0, ordered_array->el_num - 1);
}
