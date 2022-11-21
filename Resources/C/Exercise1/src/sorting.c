#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sorting.h"
#include "orderedArray.h"

static size_t binarySearch(OrderedArray *ordered_array, size_t low, size_t high, void *item) {
  size_t mid;

  if (low == high)
    return low;

  mid = low + ((high - low) / 2);

  if ((*(ordered_array->precedes))((ordered_array->array)[mid], item) > 0)
    return binarySearch(ordered_array, mid + 1, high, item);

  if ((*(ordered_array->precedes))(item, (ordered_array->array)[mid]) > 0)
    return binarySearch(ordered_array, low, mid, item);

  return mid;
}

static void insertionSortRecursive(OrderedArray *ordered_array, size_t low, size_t high) {
  size_t index = 0, i = 0;
  void *tmp;

  for (i = low + 1; i <= high; i++) {
    tmp = (ordered_array->array)[i];
    index = binarySearch(ordered_array, low, i, tmp);

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
  ssize_t low = 0;
  ssize_t high = (ssize_t) (ordered_array->el_num - 1);
  insertionSortRecursive(ordered_array, low, high);
}

long partition(OrderedArray *ordered_array, long left, long right) {

  long pivotIndex = ((left + right) / 2);

  long i = left;
  long j = right;

  while (i <= j) {
    while (i <= right && (*ordered_array->precedes)(
        ordered_array_get(ordered_array, i),
        ordered_array_get(ordered_array, pivotIndex)) > 0) {
      i++;
    }

    while (j > left && (*ordered_array->precedes)(
        ordered_array_get(ordered_array, j),
        ordered_array_get(ordered_array, pivotIndex)) < 0) {
      j--;
    }

    if (i <= j) {
      swap_array_record(ordered_array, i, j);
      i++;
      j--;
    }
  }

  return i;
}

void quickSortRecursion(OrderedArray *ordered_array, long left, long right) {
  long pi = partition(ordered_array, left, right);

  if (left < pi - 1)
    quickSortRecursion(ordered_array, left, pi - 1);
  if (pi < right)
    quickSortRecursion(ordered_array, pi, right);
}

void quickSort(OrderedArray *orderedArray) {
  quickSortRecursion(orderedArray, 0, orderedArray->el_num - 1);
}







