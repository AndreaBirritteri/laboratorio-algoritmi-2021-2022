#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sorting.h"
#include "ordered_array.h"

//It searches the index where the element should be inserted
//It accepts as input a pointer to an array, the range between
// it has to find the index defined by low and high and
// a pointer to the element
//It returns the index
//The input parameters cannot be NULL or out of bounds of the
//array
static size_t binary_search(OrderedArray *ordered_array, size_t low, size_t high, void *item) {
  size_t mid;

  if (low == high)
    return low;

  mid = low + ((high - low) / 2);

  if ((*(ordered_array->precedes))((ordered_array->array)[mid], item) > 0)
    return binary_search(ordered_array, mid + 1, high, item);

  if ((*(ordered_array->precedes))(item, (ordered_array->array)[mid]) > 0)
    return binary_search(ordered_array, low, mid, item);

  return mid;
}

//It sorts an array using the insertion sort algorithm calling
// the binarySearch to optimize the sorting.
//It accepts as input a pointer to an array and the range
// to be sorted.
//The input parameters cannot be NULL or out of bounds of the
//  array.
static void insertion_sort_recursive(OrderedArray *ordered_array, size_t low, size_t high) {
  void *tmp;

  size_t index;
  for (size_t i = low + 1; i <= high; i++) {
    tmp = (ordered_array->array)[i];
    index = binary_search(ordered_array, low, i, tmp);

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

//insertion sort wrapper
void insertion_sort(OrderedArray *ordered_array) {
  ssize_t low = 0;
  ssize_t high = (ssize_t) (ordered_array->el_num - 1);
  insertion_sort_recursive(ordered_array, low, high);
}

//partition chooses the pivot element and swaps according to
//the quick sort rules
long partition(OrderedArray *ordered_array, ssize_t left, ssize_t right) {

  ssize_t pivotIndex = ((left + right) / 2);

  ssize_t i = left;
  ssize_t j = right;

  while (i <= j) {
    while (i < right && ((*ordered_array->precedes)(
        ordered_array_get(ordered_array, i),
        ordered_array_get(ordered_array, pivotIndex))) > 0) {
      i++;
    }

    while (j >= left && ((*ordered_array->precedes)(
        ordered_array_get(ordered_array, j),
        ordered_array_get(ordered_array, pivotIndex))) < 0) {
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

//quick sort recursion method that uses the partition to divide
//the array in left and right
void quick_sort_recursion(OrderedArray *ordered_array, ssize_t left, ssize_t right) {
  long pi = partition(ordered_array, left, right);

  if (left < pi - 1)
    quick_sort_recursion(ordered_array, left, pi - 1);
  if (pi < right)
    quick_sort_recursion(ordered_array, pi, right);
}

//quick sort wrapper
void quick_sort(OrderedArray *orderedArray) {
  quick_sort_recursion(orderedArray, 0, orderedArray->el_num - 1);
}







