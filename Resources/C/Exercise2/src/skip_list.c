#include "skip_list.h"
#include <stdlib.h>
#include <time.h>

unsigned int _random_level() {
  unsigned int level = 1;

  srand(time(NULL));
  while ((rand() % 2) == 0 && level < MAX_HEIGHT) {
    level++;
  }

  return level;
}

Node *_create_node(void *item, unsigned int size) {
  Node *new_node = (Node *) malloc(sizeof(Node));

  new_node->next = (Node **) malloc(sizeof(Node *) * size);
  new_node->item = item;
  new_node->size = size;

  return new_node;
}

Node *_create_head_node() {
  Node *head_node = (Node *) malloc(sizeof(Node));

  head_node->next = (Node **) malloc(sizeof(Node *));
  head_node->item = NULL;
  head_node->size = 1;

  return head_node;
}

SkipList *create_skip_list(skip_list_comparator comparator) {
  SkipList *skip_list = (SkipList *) malloc(sizeof(SkipList));

  skip_list->head = _create_head_node();
  skip_list->compare = comparator;
  skip_list->max_level = 1;

  return skip_list;
}

void *search_skip_list(SkipList *list, void *item) {
  Node *x = list->head;
  for (size_t i = list->max_level + 1; i > 0; i--) {
    while (x->next[i - 1] != NULL && list->compare(x->next[i - 1]->item, item) > 0) {
      x = x->next[i - 1];
    }
  }
  x = x->next[0];
  if (x != NULL && list->compare(x->item, item) == 0) {
    return x->item;
  }

  return NULL;
}

void insert_skip_list(SkipList *list, void *item) {
  Node *x;
  Node *new_node = _create_node(item, _random_level());

  if (new_node->size > list->max_level) {
    list->head->next = (Node **) realloc(list->head->next, sizeof(Node *) * (new_node->size + 1));
    list->max_level = new_node->size;
  }

  x = list->head;
  for (size_t i = list->max_level + 1; i > 0; i--) {
    if (x->next[i - 1] == NULL || list->compare(item, x->next[i - 1]->item) > 0) {
      if (i - 1 < new_node->size) {
        new_node->next[i - 1] = x->next[i - 1];
        x->next[i - 1] = new_node;
      }
    } else {
      x = x->next[i - 1];
      i++;
    }
  }
}

void destroy_skip_list(SkipList *list) {
  Node *next_node;
  Node *current_node = list->head;

  while (current_node->next[0] != NULL) {
    next_node = current_node->next[0];
    free(current_node);
    current_node = next_node;
  }
}
