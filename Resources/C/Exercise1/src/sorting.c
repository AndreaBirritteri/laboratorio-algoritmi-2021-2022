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

static void startInsertionSort(OrderedArray *ordered_array, size_t high) {
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
  startInsertionSort(ordered_array, ordered_array->el_num - 1);
}

// function to find the partition position

static size_t partition(OrderedArray *ordered_array, size_t low, size_t high) {

  // select the rightmost element as pivot
  void *pivot = ordered_array_get(ordered_array, high);

  // pointer for greater element
  size_t i = (low - 1);

  //printf("%zu - %zu\n", low, high);

  // traverse each element of the array
  // compare them with the pivot
  for (size_t j = low; j < high; j++) {
    if ((*(ordered_array->precedes))(ordered_array_get(ordered_array, j), pivot)) {
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i

      //if (i > 20000000 - 3)
      //printf("%zu - %zu \n", i, i + 1);

      //if (high - low < 40000)
        //printf("%zu\n", high - low);

      //if (high - low == 100000)
      //printf("%zu - %zu \n", i, i + 1);

      //if (high - low == 1)
      //printf("%zu - %zu \n", i, i + 1);

      i++;

      // swap element at i with element at j
      swap_array_record(ordered_array, i, j);
    }
  }

  // swap the pivot element with the greater element at i
  swap_array_record(ordered_array, i + 1, high);

  // return the partition point
  return (i + 1);
}
#import <time.h>
size_t partition_r(OrderedArray *ordered_array, size_t low, size_t high)
{
  // Generate a random number in between
  // low .. high
  srand(time(NULL));
  size_t random = low + rand() % (high - low);

  // Swap A[random] with A[high]
  swap_array_record(ordered_array, random, high);

  return partition(ordered_array, low, high);
}

static void quickSortRecursive(OrderedArray *ordered_array, size_t low, size_t high, size_t arraySize) {
  if (high >= arraySize) {
    return;
  }

  if (low < high) {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    size_t pi = partition_r(ordered_array, low, high);

    // recursive call on the left of pivot
    quickSortRecursive(ordered_array, low, pi - 1, arraySize);
    // recursive call on the right of pivot

    quickSortRecursive(ordered_array, pi + 1, high, arraySize);

  }
}

void quickSort(OrderedArray *ordered_array) {
  size_t arraySize = ordered_array->el_num;
  quickSortRecursive(ordered_array, 0, ordered_array->el_num - 1, arraySize);
}
