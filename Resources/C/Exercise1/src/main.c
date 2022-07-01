#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "orderedArray.h"
#include "sorting.h"

struct record {
    int int_id;
    char *string_field1;
    int int_field2;
    float float_field3;
};

//It takes as input two pointers to struct record.
//It returns 1 iff the string field of the first record is less than
//the string field of the second one (0 otherwise)
static int precedes_record_string_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_string: the first parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_string: the second parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record *) r1_p;
  struct record *rec2_p = (struct record *) r2_p;
  if (strcmp(rec1_p->string_field1, rec2_p->string_field1) < 0) {
    return (1);
  }
  return (0);
}

//It takes as input two pointers to struct record.
//It returns 1 iff the integer field of the first record is less than
//the integer field of the second one (0 otherwise)
static int precedes_record_int_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record *) r1_p;
  struct record *rec2_p = (struct record *) r2_p;
  if (rec1_p->int_field2 < rec2_p->int_field2) {
    return (1);
  }
  return (0);
}

//It takes as input two pointers to struct record.
//It returns 1 iff the integer field of the first record is less than
//the integer field of the second one (0 otherwise)
static int precedes_record_float_field(void *r1_p, void *r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the first parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "precedes_record_int_field: the second parameter is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record *) r1_p;
  struct record *rec2_p = (struct record *) r2_p;
  if (rec1_p->float_field3 < rec2_p->float_field3) {
    return (1);
  }
  return (0);
}

static void free_array(OrderedArray *array) {
  size_t el_num = ordered_array_size(array), i;
  for (i = 0; i < el_num; i++) {
    struct record *array_element = (struct record *) ordered_array_get(array, i);
    free(array_element->string_field1);
    free(array_element);
  }
  ordered_array_free_memory(array);
}

static void load_array(const char *file_name, OrderedArray *array) {
  char *read_line_p;
  int buf_size = 1024;
  char buffer[buf_size];
  FILE *fp;

  printf("\nLoading data...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "main: unable to open the file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, buf_size, fp) != NULL) {
    read_line_p = malloc((strlen(buffer) + 1) * sizeof(char));
    if (read_line_p == NULL) {
      fprintf(stderr, "main: unable to allocate memory for the read line");
      exit(EXIT_FAILURE);
    }
    strcpy(read_line_p, buffer);

    char *id_field_in_read_line_p = strtok(read_line_p, ",");
    char *string_field_in_read_line_p = strtok(NULL, ",");
    char *int_field_in_read_line_p = strtok(NULL, ",");
    char *float_field_in_read_line_p = strtok(NULL, ",");
    char *string_field = malloc((strlen(string_field_in_read_line_p) + 1) * sizeof(char));
    if (string_field == NULL) {
      fprintf(stderr, "main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }

    int id_field = atoi(id_field_in_read_line_p);
    strcpy(string_field, string_field_in_read_line_p);
    int int_field = atoi(int_field_in_read_line_p);
    float float_field = (float) atof(float_field_in_read_line_p);
    struct record *record_p = malloc(sizeof(struct record));
    if (record_p == NULL) {
      fprintf(stderr, "main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }

    record_p->int_id = id_field;
    record_p->string_field1 = string_field;
    record_p->int_field2 = int_field;
    record_p->float_field3 = float_field;

    ordered_array_add(array, (void *) record_p);
    free(read_line_p);
  }
  fclose(fp);
}

static void test_with_comparison_function(const char *file_name, const char *method, int (*compare)(void *, void *)) {
  double time_taken = 0;
  struct timeval start, end;

  OrderedArray *array = ordered_array_create(compare);

  gettimeofday(&start, NULL);
  load_array(file_name, array);
  gettimeofday(&end, NULL);
  time_taken = (double) end.tv_sec + (double) end.tv_usec / 1e6 - (double) start.tv_sec - (double) start.tv_usec / 1e6;
  printf("\nData loaded: %fs\n", time_taken);

  time_taken = 0;

  gettimeofday(&start, NULL);

  if (strcmp(method, "0") == 0)
    insertionSort(array);
  else if (strcmp(method, "1") == 0)
    quickSort(array);
  else {
    fprintf(stderr, "%s not admitted. You must use 0 for Binary Insertion Sort, or 1 for Quick Sort", method);
    exit(EXIT_FAILURE);
  }

  gettimeofday(&end, NULL);
  time_taken = (double) end.tv_sec + (double) end.tv_usec / 1e6 - (double) start.tv_sec - (double) start.tv_usec / 1e6;

  printf("\nArray ordered in: %fs\n\n", time_taken);
  print_array(array);
  free_array(array);
}

//It should be invoked with two parameter specifying the filepath of the data file
//and the algorithm method
//0: binary insertion sort
//1: quick sort
int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Usage: ordered_array_main <file_name> <method>\n");
    printf("<method>:\n");
    printf("\t0 - Binary Insertion Sort\n");
    printf("\t1 - Quick Sort\n");
    exit(EXIT_FAILURE);
  }
  if (strcmp(argv[2], "0") != 0 && strcmp(argv[2], "1") != 0)
  {
    fprintf(stderr, "\"%s\" not admitted. You must use 0 for Binary Insertion Sort, or 1 for Quick Sort", argv[2]);
    exit(EXIT_FAILURE);
  }

  printf("\n------------STRING------------\n");
  test_with_comparison_function(argv[1], argv[2], precedes_record_string_field);
  printf("\n\n------------INT------------\n");
  test_with_comparison_function(argv[1], argv[2], precedes_record_int_field);
  printf("\n\n------------FLOAT------------\n");
  test_with_comparison_function(argv[1], argv[2], precedes_record_float_field);

  return (EXIT_SUCCESS);
}
