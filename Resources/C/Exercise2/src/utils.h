#ifndef UTILS_H
#define UTILS_H

#include "skip_list.h"

#define MAX_WORD_LENGTH 100

void print_typos(SkipList *dictionary, char **word_list, size_t word_list_length);

char **load_text(const char *path, size_t *word_list_size_argument);

SkipList *load_dictionary(const char *path);

#endif
