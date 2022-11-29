#include <string.h>
#include "../../Unity/unity.h"
#include "skip_list.h"

static int string_comparator(char *a, char *b) {
  return strcmp(a, b);
}

static int float_comparator(float *a, float *b) {
  return (int) (a - b);
}

SkipList *string_skip_list, *float_skip_list;
char *strings_to_insert[3];
float floats_to_insert[3];

void setUp(void) {
  strings_to_insert[0] = "AA";
  strings_to_insert[1] = "BB";
  strings_to_insert[2] = "CC";

  floats_to_insert[0] = -4324.43f;
  floats_to_insert[1] = 0;
  floats_to_insert[2] = 4329.12f;


  string_skip_list = create_skip_list((skip_list_comparator) string_comparator);
  float_skip_list = create_skip_list((skip_list_comparator) float_comparator);
}

void tearDown(void) {
  destroy_skip_list(string_skip_list);
  destroy_skip_list(float_skip_list);
}

static void insert_one_element(void) {
  insert_skip_list(string_skip_list, strings_to_insert[0]);
  insert_skip_list(float_skip_list, &floats_to_insert[0]);

  char *string_found;
  float *float_found;
  Node *x;

  x = string_skip_list->head;
  for (int i = 0; i < string_skip_list->max_level; i++) {
    if (x->next[i] != NULL) {
      x = x->next[i];
    }
  }
  string_found = x->item;

  x = float_skip_list->head;
  for (int i = 0; i < float_skip_list->max_level; i++) {
    if (x->next[i] != NULL) {
      x = x->next[i];
    }
  }
  float_found = (float *) x->item;

  TEST_ASSERT_EQUAL_STRING(strings_to_insert[0], string_found);

  TEST_ASSERT_EQUAL_FLOAT(floats_to_insert[0], *float_found);
}

static void insert_three_elements(void) {
  insert_skip_list(string_skip_list, strings_to_insert[1]);
  insert_skip_list(string_skip_list, strings_to_insert[2]);
  insert_skip_list(string_skip_list, strings_to_insert[0]);

  insert_skip_list(float_skip_list, &floats_to_insert[1]);
  insert_skip_list(float_skip_list, &floats_to_insert[2]);
  insert_skip_list(float_skip_list, &floats_to_insert[0]);

  char *strings_found[3];
  strings_found[0] = NULL;
  strings_found[1] = NULL;
  strings_found[2] = NULL;

  float *floats_found[3];
  floats_found[0] = NULL;
  floats_found[1] = NULL;
  floats_found[2] = NULL;

  Node *x;

  x = string_skip_list->head;
  for (int i = 0; i < string_skip_list->max_level; i++) {
    while (x->next[i] != NULL) {
      Node *this_node = x->next[i];
      for (int j = 0; j < 3; j++) {
        if (this_node->item == strings_to_insert[j]) {
          strings_found[j] = this_node->item;
        }
      }
      x = *x->next;
    }
  }

  x = float_skip_list->head;
  for (int i = 0; i < float_skip_list->max_level; i++) {
    while (x->next[i] != NULL) {
      Node *this_node = x->next[i];
      for (int j = 0; j < 3; j++) {
        if (*(float *) this_node->item == floats_to_insert[j]) {
          floats_found[j] = (float *) this_node->item;
        }
      }
      x = *x->next;
    }
  }


  TEST_ASSERT_EQUAL_STRING(strings_to_insert[0], strings_found[0]);
  TEST_ASSERT_EQUAL_STRING(strings_to_insert[1], strings_found[1]);
  TEST_ASSERT_EQUAL_STRING(strings_to_insert[2], strings_found[2]);

  TEST_ASSERT_EQUAL_FLOAT(floats_to_insert[0], *floats_found[0]);
  TEST_ASSERT_EQUAL_FLOAT(floats_to_insert[1], *floats_found[1]);
  TEST_ASSERT_EQUAL_FLOAT(floats_to_insert[2], *floats_found[2]);
}

static void search_three_elements() {
  insert_skip_list(string_skip_list, strings_to_insert[1]);
  insert_skip_list(string_skip_list, strings_to_insert[2]);
  insert_skip_list(string_skip_list, strings_to_insert[0]);

  insert_skip_list(float_skip_list, &floats_to_insert[1]);
  insert_skip_list(float_skip_list, &floats_to_insert[2]);
  insert_skip_list(float_skip_list, &floats_to_insert[0]);

  void *strings_found[3];
  strings_found[0] = search_skip_list(string_skip_list, strings_to_insert[0]);
  strings_found[1] = search_skip_list(string_skip_list, strings_to_insert[1]);
  strings_found[2] = search_skip_list(string_skip_list, strings_to_insert[2]);

  float *floats_found[3];
  floats_found[0] = search_skip_list(float_skip_list, &floats_to_insert[0]);
  floats_found[1] = search_skip_list(float_skip_list, &floats_to_insert[1]);
  floats_found[2] = search_skip_list(float_skip_list, &floats_to_insert[2]);

  TEST_ASSERT_EQUAL(strings_to_insert[0], strings_found[0]);
  TEST_ASSERT_EQUAL(strings_to_insert[1], strings_found[1]);
  TEST_ASSERT_EQUAL(strings_to_insert[2], strings_found[2]);

  TEST_ASSERT_EQUAL_FLOAT(floats_to_insert[0], *floats_found[0]);
  TEST_ASSERT_EQUAL_FLOAT(floats_to_insert[1], *floats_found[1]);
  TEST_ASSERT_EQUAL_FLOAT(floats_to_insert[2], *floats_found[2]);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(insert_one_element);
  RUN_TEST(insert_three_elements);
  RUN_TEST(search_three_elements);
  return UNITY_END();
}