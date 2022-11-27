#include <string.h>
#include <stdlib.h>
#include "../../Unity/unity.h"
#include "skip_list.h"
#include "utils.h"

static int string_comparator(char *a, char *b) {
  return strcmp(a, b);
}

SkipList *skip_list;
char *items_to_insert[3];

void setUp(void) {
  items_to_insert[0] = "AA";
  items_to_insert[1] = "BB";
  items_to_insert[2] = "CC";


  skip_list = create_skip_list((skip_list_comparator) string_comparator);
}

void tearDown(void) {
  destroy_skip_list(skip_list);
}

static void insert_one_element(void) {
  insert_skip_list(skip_list, items_to_insert[0]);

  Node *x = skip_list->head;
  for (int i = 0; i < skip_list->max_level; i++) {
    if (x->next[i] != NULL) {
      x = x->next[i];
    }
  }

  TEST_ASSERT_EQUAL(items_to_insert[0], x->item);
}

static void insert_three_elements(void) {
  insert_skip_list(skip_list, items_to_insert[0]);
  insert_skip_list(skip_list, items_to_insert[1]);
  insert_skip_list(skip_list, items_to_insert[2]);

  void *items_found[3];
  items_found[0] = NULL;
  items_found[1] = NULL;
  items_found[2] = NULL;

  Node *x = skip_list->head;
  for (int i = 0; i < skip_list->max_level; i++) {
    while (x->next[i] != NULL) {
      Node *this_node = x->next[i];
      for (int j = 0; j < 3; j++) {
        if (this_node->item == items_to_insert[j]) {
          items_found[j] = this_node->item;
        }
      }
      x = *x->next;
    }
  }

  TEST_ASSERT_EQUAL(items_to_insert[0], items_found[0]);
  TEST_ASSERT_EQUAL(items_to_insert[1], items_found[1]);
  TEST_ASSERT_EQUAL(items_to_insert[2], items_found[2]);
}

static void search_three_elements(){
  insert_skip_list(skip_list, items_to_insert[0]);
  insert_skip_list(skip_list, items_to_insert[1]);
  insert_skip_list(skip_list, items_to_insert[2]);

  void *items_found[3];
  items_found[0] = search_skip_list(skip_list, items_to_insert[0]);
  items_found[1] = search_skip_list(skip_list, items_to_insert[1]);
  items_found[2] = search_skip_list(skip_list, items_to_insert[2]);

  TEST_ASSERT_EQUAL(items_to_insert[0], items_found[0]);
  TEST_ASSERT_EQUAL(items_to_insert[1], items_found[1]);
  TEST_ASSERT_EQUAL(items_to_insert[2], items_found[2]);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(insert_one_element);
  RUN_TEST(insert_three_elements);
  RUN_TEST(search_three_elements);
  return UNITY_END();
}