#include "utils.h"
#include "skip_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static int _string_comparator(char *a, char *b) {
  return strcmp(a, b);
}

unsigned int _is_punctuation(const char character) {
  unsigned int is_punctuation = 0;
  char punctuation_symbols[] = {' ', '.', ',', ':'};

  for (int i = 0; is_punctuation == 0 && i < 4; i++) {
    if (punctuation_symbols[i] == character) {
      is_punctuation = 1;
    }
  }
  return is_punctuation;
}

void print_typos(SkipList *dictionary, char **word_list, size_t word_list_length) {
  char *word_found;

  for (size_t i = 0; i < word_list_length; i++) {
    word_found = (char *) search_skip_list(dictionary, word_list[i]);
    if (word_found == NULL) {
      printf("%s\n", word_list[i]);
    }
  }
}

char **load_word_list(const char *path, size_t *word_list_size_argument) {
  FILE *fp;
  fp = fopen(path, "r");
  if (fp == NULL) {
    fprintf(stderr, "Impossible to open word list file");
    exit(EXIT_FAILURE);
  }

  char **word_list = (char **) malloc(sizeof(char *));
  char *line = NULL;
  size_t word_list_size_local = 0;
  size_t length = 0;
  while ((getline(&line, &length, fp)) != -1) {
    char *current_word = (char *) malloc(sizeof(char) * MAX_WORD_LENGTH);
    size_t letter_index = 0;
    for (int i = 0; i < length; i++) {
      if (_is_punctuation(line[i])) {
        if (letter_index > 0) {
          word_list_size_local++;
          word_list = (char **) realloc(word_list, sizeof(char *) * (word_list_size_local));

          char *word_to_insert = (char *) malloc(sizeof(char) * letter_index);
          strcpy(word_to_insert, current_word);
          for (int n = 0; word_to_insert[n]; n++) {
            word_to_insert[n] = (char) tolower(word_to_insert[n]);
          }
          word_list[word_list_size_local - 1] = word_to_insert;

          current_word = (char *) malloc(sizeof(char) * MAX_WORD_LENGTH);
          letter_index = 0;
        }
      } else { //is not punctuation
        current_word[letter_index] = line[i];
        letter_index++;
      }
    }
  }

  *word_list_size_argument = word_list_size_local;
  return word_list;
}

SkipList *load_dictionary(const char *path) {
  size_t length = 0, word_length;
  SkipList *dictionary;
  char *line = NULL;
  char *word;
  FILE *fp;

  dictionary = create_skip_list((skip_list_comparator) _string_comparator);
  fp = fopen(path, "r");
  if (fp == NULL) {
    fprintf(stderr, "Impossible to open dictionary file");
    exit(EXIT_FAILURE);
  }
  while ((getline(&line, &length, fp)) != -1) {
    word_length = strlen(line);
    word = (char *) malloc(sizeof(char) * (word_length - 1));
    memcpy(word, line, word_length - 1);
    insert_skip_list(dictionary, word);
  }
  return dictionary;
}
