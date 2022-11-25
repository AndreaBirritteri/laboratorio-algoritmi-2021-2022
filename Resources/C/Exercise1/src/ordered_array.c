#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ordered_array.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2

void swap_array_record(OrderedArray *ordered_array, size_t i, size_t j) {
  if(i + 1 == 0){
    fprintf(stderr, "swap_array_record: Index i -1 is out of the array bounds");
    exit(EXIT_FAILURE);
  }
  if(j + 1 == 0){
    fprintf(stderr, "swap_array_record: Index j -1 is out of the array bounds");
    exit(EXIT_FAILURE);
  }
  if (i >= ordered_array->el_num) {
    fprintf(stderr, "swap_array_record: Index i %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  if (j >= ordered_array->el_num) {
    fprintf(stderr, "swap_array_record: Index j %lu is out of the array bounds", j);
    exit(EXIT_FAILURE);
  }

  void* temp = ordered_array->array[i];
  ordered_array->array[i] = ordered_array->array[j];
  ordered_array->array[j] = temp;
}

OrderedArray *ordered_array_create(int (*precedes)(void *, void *)) {
  if (precedes == NULL) {
    fprintf(stderr, "ordered_array_create: precedes parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  OrderedArray *ordered_array = (OrderedArray *) malloc(sizeof(OrderedArray));
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
    exit(EXIT_FAILURE);
  }
  ordered_array->array = (void **) malloc(INITIAL_CAPACITY * sizeof(void *));
  if (ordered_array->array == NULL) {
    fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  ordered_array->el_num = 0;
  ordered_array->array_capacity = INITIAL_CAPACITY;
  ordered_array->precedes = precedes;

  return (ordered_array);
}

int ordered_array_is_empty(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_is_empty: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (ordered_array->el_num == 0)
    return (1);
  return (0);
}

size_t ordered_array_size(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_size: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return (ordered_array->el_num);
}

void ordered_array_add(OrderedArray *ordered_array, void *element) {
  if (ordered_array == NULL) {
    fprintf(stderr, "add_ordered_array_element: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (element == NULL) {
    fprintf(stderr, "add_ordered_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if (ordered_array->el_num >= ordered_array->array_capacity) {
    ordered_array->array = (void **) realloc(ordered_array->array,
                                             2 * (ordered_array->array_capacity) * sizeof(void *));
    if (ordered_array->array == NULL) {
      fprintf(stderr, "ordered_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
    ordered_array->array_capacity = 2 * ordered_array->array_capacity;
  }

  (ordered_array->array)[ordered_array->el_num] = element;
  (ordered_array->el_num)++;
}

void *ordered_array_get(OrderedArray *ordered_array, size_t i) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= ordered_array->el_num) {
    fprintf(stderr, "ordered_array_get: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return (ordered_array->array)[i];
}

struct record { //TODO check were write this
  int int_id;
  char *string_field1;
  int int_field2;
  float float_field3;
};

void print_array(OrderedArray *ordered_array) {
  int c = 0;
  struct record *rec;

  for (c = 0; c < ordered_array->el_num; c++) {
    rec = ordered_array_get(ordered_array, c);
    printf("%d,\t\t%s,\t\t%d,\t\t%f\n", rec->int_id, rec->string_field1, rec->int_field2, rec->float_field3);
  }
}

void ordered_array_free_memory(OrderedArray *ordered_array) {
  if (ordered_array == NULL) {
    fprintf(stderr, "ordered_array_free_memory: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(ordered_array->array);
  free(ordered_array);
}


