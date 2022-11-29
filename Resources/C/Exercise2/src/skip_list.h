#ifndef LIB_SORT_H
#define LIB_SORT_H

#define MAX_HEIGHT 50
#include <stdio.h>

typedef int (*skip_list_comparator)(const void *, const void *);

typedef struct _SkipList SkipList;
typedef struct _Node Node;

struct _Node {
  unsigned int size;
  Node **next;
  void *item;
};

struct _SkipList {
  skip_list_comparator compare;
  unsigned int max_level;
  Node *head;
};

SkipList *create_skip_list(skip_list_comparator comparator);

void insert_skip_list(SkipList *list, void *item);

void *search_skip_list(SkipList *list, void *i);

void destroy_skip_list(SkipList *list);

#endif