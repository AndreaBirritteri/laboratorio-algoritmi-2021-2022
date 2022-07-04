#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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
static ssize_t partition(OrderedArray *ordered_array, ssize_t low, ssize_t high) {
  ssize_t midPosition = (high - low) / 2;
  swap_array_record(ordered_array, low, midPosition);

  void *pivot = ordered_array_get(ordered_array, low);
  ssize_t i = low + 1;
  ssize_t j = high;

  //printf("%zu - %zu\n", low, high);

  while (i <= j) {
    //printf("%d\n", j - i);
    if ((*(ordered_array->precedes))(ordered_array_get(ordered_array, i), pivot) > 0) {
      i = i + 1;
    } else {
      if (((*(ordered_array->precedes))(ordered_array_get(ordered_array, j), pivot)) <= 0) {
        j = j - 1;
      } else {
        swap_array_record(ordered_array, i, j);
        //printf("swap %d, %d \n", i, j);
        i = i + 1;
        j = j - 1;
      }
    }
  }
  swap_array_record(ordered_array, low, j);
  //printf("swap low %d, %d \n", low, j);

  //print_array(ordered_array);
  return j;
}

static void quickSortRecursive(OrderedArray *ordered_array, ssize_t low, ssize_t high) {
  //printf(" low: %d - high: %d\n");

  if (high - low + 1 > 1) {
    //printf("%d size \n", high - low);
    ssize_t pi = partition(ordered_array, low, high);
    //printf("%d pi \n", pi);

    quickSortRecursive(ordered_array, low, pi);

    quickSortRecursive(ordered_array, pi + 1, high);

  }
}

void quickSort(OrderedArray *ordered_array) {
  quickSortRecursive(ordered_array, 0, (ssize_t) (ordered_array->el_num) - 1);
}
