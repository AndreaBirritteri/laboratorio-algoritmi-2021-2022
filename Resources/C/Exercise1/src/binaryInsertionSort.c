#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "link.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2

//It represents the internal structure of this implementation of ordered arrays
struct _OrderedArray
{
    void **array;
    size_t el_num; //numero di elementi
    size_t array_capacity; //capacita dell'array
    int (*precedes)(void *, void *);
};

//It searches the index where the element should be inserted
//It accepts as input a pointer to an array, the range between
// it has to find the index defined by low and high and
// a pointer to the element
//It returns the index
//The input parameters cannot be NULL or out of bounds of the
//array
static size_t binarySearch(OrderedArray *ordered_array, size_t low, size_t high, void *item);

//It sorts an array using the insertion sort algorithm calling
// the binarySearch to optimize the sorting.
//It accepts as input a pointer to an array and the range
// to be sorted.
//The input parameters cannot be NULL or out of bounds of the
//  array.
static void insertionSort(OrderedArray *ordered_array, size_t low, size_t high);

OrderedArray *ordered_array_create(int (*precedes)(void *, void *))
{
  if (precedes == NULL)
  {
    fprintf(stderr, "ordered_array_create: precedes parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  OrderedArray *ordered_array = (OrderedArray *)malloc(sizeof(OrderedArray));
  if (ordered_array == NULL)
  {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  ordered_array->array = (void **)malloc(INITIAL_CAPACITY * sizeof(void *));
  if (ordered_array->array == NULL)
  {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  ordered_array->el_num = 0;
  ordered_array->array_capacity = INITIAL_CAPACITY;
  ordered_array->precedes = precedes;

  return (ordered_array);
}

int ordered_array_is_empty(OrderedArray *ordered_array)
{
  if (ordered_array == NULL)
  {
    fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (ordered_array->el_num == 0)
    return (1);
  return (0);
}

size_t ordered_array_size(OrderedArray *ordered_array)
{
  if (ordered_array == NULL)
  {
    fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return (ordered_array->el_num);
}

void ordered_array_add(OrderedArray *ordered_array, void *element)
{
  if (ordered_array == NULL)
  {
    fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (element == NULL)
  {
    fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (ordered_array->el_num >= ordered_array->array_capacity)
  {
    ordered_array->array = (void **)realloc(ordered_array->array, 2 * (ordered_array->array_capacity) * sizeof(void *));
    if (ordered_array->array == NULL)
    {
      fprintf(stderr, "ordered_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
    ordered_array->array_capacity = 2 * ordered_array->array_capacity;
  }

  (ordered_array->array)[ordered_array->el_num] = element;
  (ordered_array->el_num)++;
}

void *ordered_array_get(OrderedArray *ordered_array, size_t i)
{
  if (ordered_array == NULL)
  {
    fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= ordered_array->el_num)
  {
    fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return (ordered_array->array)[i];
}

void ordered_array_free_memory(OrderedArray *ordered_array)
{
  if (ordered_array == NULL)
  {
    fprintf(stderr, "ordered_array_free_memory: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(ordered_array->array);
  free(ordered_array);
}

static size_t binarySearch(OrderedArray *ordered_array, size_t low, size_t high, void *item)
{
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


void performInsertionSort(OrderedArray *ordered_array)
{
  insertionSort(ordered_array, 0, ordered_array->el_num - 1);
}

static void insertionSort(OrderedArray *ordered_array, size_t low, size_t high)
{
  size_t index = 0, i = 0;
  void *tmp;

  for (i = low + 1; i <= high; i++)
  {
    tmp = (ordered_array->array)[i];
    index = binarySearch(ordered_array, low, i, tmp);

    if (index > high)
    {
      fprintf(stderr, "insertion_sort: index out of bounds of the array");
      exit(EXIT_FAILURE);
    }

    if (index < i)
    {
      memmove((ordered_array->array) + index + 1, (ordered_array->array) + index, sizeof(void *) * (i - index));
      (ordered_array->array)[index] = tmp;
    }
  }
}
