#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "utils.h"
#include "skip_list.h"


int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "You have to input <items path> <file to correct path>.\n");
    exit(EXIT_FAILURE);
  }

  char *dictionary_path = argv[1];
  char *text_path = argv[2];

  struct timeval start, end;
  double time_taken = 0;

  SkipList *dictionary;

  printf("Loading dictionary...\n");
  gettimeofday(&start, NULL);
  dictionary = load_dictionary(dictionary_path);
  gettimeofday(&end, NULL);
  time_taken = (double) end.tv_sec + (double) end.tv_usec / 1e6 - (double) start.tv_sec - (double) start.tv_usec / 1e6;
  printf("dictionary loaded in %fs!\n", time_taken);


  size_t number_of_words = 0;
  char **word_list;
  printf("Loading word list to check...\n");
  gettimeofday(&start, NULL);
  word_list = load_text(text_path, &number_of_words);
  gettimeofday(&end, NULL);
  printf("Typos found:\n");
  print_typos(dictionary, word_list, number_of_words);

  time_taken = (double) end.tv_sec + (double) end.tv_usec / 1e6 - (double) start.tv_sec - (double) start.tv_usec / 1e6;
  printf("Text corrected in %fs!\n", time_taken);

  destroy_skip_list(dictionary);
  return 0;
}
