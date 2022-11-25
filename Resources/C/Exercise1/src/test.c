#include <string.h>
#include <stdlib.h>
#include "../../Unity/unity.h"
#include "ordered_array.h"
#include "sorting.h"
/*
 * Test suite for ordered array data structure and algorithms
 */

//precedence relation used in tests
static int precedes_int(void *i1_p, void *i2_p) {
  int *int1_p = (int *) i1_p;
  int *int2_p = (int *) i2_p;
  if ((*int1_p) < (*int2_p))
    return (1);
  if ((*int1_p) > (*int2_p))
    return (-1);
  return (0);
}

//precedence relation used in tests
static int precedes_string(void *s1_p, void *s2_p) {
  char *string1_p = (char *) s1_p;
  char *string2_p = (char *) s2_p;
  if ((strcmp(string1_p, string2_p)) < 0)
    return (1);
  if ((strcmp(string1_p, string2_p)) > 0)
    return (-1);
  return (0);
}

//precedence relation used in tests
static int precedes_float(void *f1_p, void *f2_p) {
  float *float1_p = (float *) f1_p;
  float *float2_p = (float *) f2_p;
  if ((*float1_p) < (*float2_p))
    return (1);
  if ((*float1_p) > (*float2_p))
    return (-1);
  return (0);
}

//Data elements that are initialized before each test
static int i1, i2, i3;
static char *s1, *s2, *s3;
static float f1, f2, f3;

static OrderedArray *ordered_array_int, *ordered_array_string, *ordered_array_float;

void setUp(void) {
  i1 = -12;
  i2 = 0;
  i3 = 4;
  s1 = "";
  s2 = "ciao";
  s3 = "#stringa?lunghissima_con:caratteri+e5numeri1";
  f1 = (float) -1234.2139;
  f2 = (float) 0.0;
  f3 = (float) 32402.23142134;
  ordered_array_int = ordered_array_create(precedes_int);
  ordered_array_string = ordered_array_create(precedes_string);
  ordered_array_float = ordered_array_create(precedes_float);
}

void tearDown(void) {
  ordered_array_free_memory(ordered_array_int);
  ordered_array_free_memory(ordered_array_string);
  ordered_array_free_memory(ordered_array_float);
}

static void test_are_empty_zero_el(void) {
  TEST_ASSERT_TRUE(ordered_array_is_empty(ordered_array_int) && ordered_array_is_empty(ordered_array_string) &&
                   ordered_array_is_empty(ordered_array_float));
}

static void test_are_empty_one_el(void) {
  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_string, s1);
  ordered_array_add(ordered_array_float, &f1);
  TEST_ASSERT_FALSE(ordered_array_is_empty(ordered_array_int) && ordered_array_is_empty(ordered_array_string) &&
                    ordered_array_is_empty(ordered_array_float));
}

static void test_size_zero_el(void) {
  TEST_ASSERT_EQUAL_INT(0, ordered_array_size(ordered_array_int));
  TEST_ASSERT_EQUAL_INT(0, ordered_array_size(ordered_array_string));
  TEST_ASSERT_EQUAL_INT(0, ordered_array_size(ordered_array_float));
}

static void test_size_one_el(void) {
  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_string, s1);
  ordered_array_add(ordered_array_float, &f1);

  TEST_ASSERT_EQUAL_INT(1, ordered_array_size(ordered_array_int));
  TEST_ASSERT_EQUAL_INT(1, ordered_array_size(ordered_array_string));
  TEST_ASSERT_EQUAL_INT(1, ordered_array_size(ordered_array_float));
}

static void test_size_two_el(void) {
  ordered_array_add(ordered_array_int, &i3);
  ordered_array_add(ordered_array_int, &i2);
  ordered_array_add(ordered_array_string, s3);
  ordered_array_add(ordered_array_string, s2);
  ordered_array_add(ordered_array_float, &f3);
  ordered_array_add(ordered_array_float, &f2);

  TEST_ASSERT_EQUAL_INT(2, ordered_array_size(ordered_array_int));
  TEST_ASSERT_EQUAL_INT(2, ordered_array_size(ordered_array_string));
  TEST_ASSERT_EQUAL_INT(2, ordered_array_size(ordered_array_float));
}

static void test_size_three_el(void) {
  ordered_array_add(ordered_array_int, &i2);
  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_int, &i3);
  ordered_array_add(ordered_array_string, s2);
  ordered_array_add(ordered_array_string, s1);
  ordered_array_add(ordered_array_string, s3);
  ordered_array_add(ordered_array_float, &f2);
  ordered_array_add(ordered_array_float, &f1);
  ordered_array_add(ordered_array_float, &f3);

  TEST_ASSERT_EQUAL_INT(3, ordered_array_size(ordered_array_int));
  TEST_ASSERT_EQUAL_INT(3, ordered_array_size(ordered_array_string));
  TEST_ASSERT_EQUAL_INT(3, ordered_array_size(ordered_array_float));
}

static void test_add_get_one_el(void) {
  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_string, s2);
  ordered_array_add(ordered_array_float, &f3);

  TEST_ASSERT_EQUAL_PTR(&i1, ordered_array_get(ordered_array_int, 0));
  TEST_ASSERT_EQUAL_PTR(s2, ordered_array_get(ordered_array_string, 0));
  TEST_ASSERT_EQUAL_PTR(&f3, ordered_array_get(ordered_array_float, 0));
}

static void test_add_get_three_el(void) {
  int *exp_int[] = {&i1, &i2, &i3};
  char *exp_str[] = {s1, s2, s3};
  float *exp_float[] = {&f1, &f2, &f3};

  size_t i;

  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_int, &i2);
  ordered_array_add(ordered_array_int, &i3);
  ordered_array_add(ordered_array_string, s1);
  ordered_array_add(ordered_array_string, s2);
  ordered_array_add(ordered_array_string, s3);
  ordered_array_add(ordered_array_float, &f1);
  ordered_array_add(ordered_array_float, &f2);
  ordered_array_add(ordered_array_float, &f3);

  int **act_int = malloc(3 * sizeof(int *));
  char **act_str = malloc(3 * sizeof(char *));
  float **act_float = malloc(3 * sizeof(float *));

  for (i = 0; i < 3; i++) {
    act_int[i] = (int *) ordered_array_get(ordered_array_int, i);
    act_str[i] = (char *) ordered_array_get(ordered_array_string, i);
    act_float[i] = (float *) ordered_array_get(ordered_array_float, i);
  }

  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_int, act_int, 3);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_str, act_str, 3);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_float, act_float, 3);
}

static void test_insertion_sort_three_el(void) {
  int *exp_int[] = {&i1, &i2, &i3};
  char *exp_str[] = {s1, s3, s2};
  float *exp_float[] = {&f1, &f2, &f3};

  ordered_array_add(ordered_array_int, &i3);
  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_int, &i2);
  ordered_array_add(ordered_array_string, s3);
  ordered_array_add(ordered_array_string, s2);
  ordered_array_add(ordered_array_string, s1);
  ordered_array_add(ordered_array_float, &f3);
  ordered_array_add(ordered_array_float, &f1);
  ordered_array_add(ordered_array_float, &f2);

  insertion_sort(ordered_array_int);
  insertion_sort(ordered_array_string);
  insertion_sort(ordered_array_float);

  int **act_int = malloc(3 * sizeof(int *));
  char **act_str = malloc(3 * sizeof(char *));
  float **act_float = malloc(3 * sizeof(float *));

  size_t i;

  for (i = 0; i < 3; i++) {
    act_int[i] = (int *) ordered_array_get(ordered_array_int, i);
    act_str[i] = (char *) ordered_array_get(ordered_array_string, i);
    act_float[i] = (float *) ordered_array_get(ordered_array_float, i);
  }

  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_int, act_int, 3);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_str, act_str, 3);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_float, act_float, 3);
}


static void test_quick_sort_three_el(void) {
  int *exp_int[] = {&i1, &i2, &i3};
  char *exp_str[] = {s1, s3, s2};
  float *exp_float[] = {&f1, &f2, &f3};

  ordered_array_add(ordered_array_int, &i3);
  ordered_array_add(ordered_array_int, &i1);
  ordered_array_add(ordered_array_int, &i2);
  ordered_array_add(ordered_array_string, s3);
  ordered_array_add(ordered_array_string, s2);
  ordered_array_add(ordered_array_string, s1);
  ordered_array_add(ordered_array_float, &f3);
  ordered_array_add(ordered_array_float, &f1);
  ordered_array_add(ordered_array_float, &f2);

  quick_sort(ordered_array_int);
  quick_sort(ordered_array_string);
  quick_sort(ordered_array_float);

  int **act_int = malloc(3 * sizeof(int *));
  char **act_str = malloc(3 * sizeof(char *));
  float **act_float = malloc(3 * sizeof(float *));

  size_t i;

  for (i = 0; i < 3; i++) {
    act_int[i] = (int *) ordered_array_get(ordered_array_int, i);
    act_str[i] = (char *) ordered_array_get(ordered_array_string, i);
    act_float[i] = (float *) ordered_array_get(ordered_array_float, i);
  }

  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_int, act_int, 3);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_str, act_str, 3);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_float, act_float, 3);
}


int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_are_empty_zero_el);
  RUN_TEST(test_are_empty_one_el);
  RUN_TEST(test_size_zero_el);
  RUN_TEST(test_size_one_el);
  RUN_TEST(test_size_two_el);
  RUN_TEST(test_size_three_el);
  RUN_TEST(test_add_get_one_el);
  RUN_TEST(test_add_get_three_el);
  RUN_TEST(test_insertion_sort_three_el);
  RUN_TEST(test_quick_sort_three_el);

  return UNITY_END();
}
