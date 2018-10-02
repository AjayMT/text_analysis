
// zipf.c
//
// This program reads text from stdin up to a certain number of characters
// (specified as a command-line argument) and then uses text_analysis.c
// to construct a word frequency map and sort words in descending order of
// frequency, in an attempt to demonstrate the pattern described by Zipf's Law.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_analysis.c"

int compare_word_frequency (const void *a, const void *b)
{
  return ((wordmap *)a)->frequency - ((wordmap *)b)->frequency;
}

int main (int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage: zipf <file-size>\n");
    return 0;
  }

  if (TA_streq(argv[1], "help")) {
    printf("Usage: zipf <file-size>\n");
    return 0;
  }

  unsigned long textsize = atol(argv[1]);
  char *text = calloc(textsize, sizeof(char));
  char sep = ':';

  unsigned long i;
  for (i = 0; i < textsize; i++) {
    char c = getchar();
    if (c == EOF) break;
    text[i] = c;
  }

  text[i] = '\0';

  char *lowercase = TA_to_lowercase(
    calloc(strlen(text), sizeof(char)),
    text
    );
  char *all_words = TA_extract_words(
    calloc(strlen(lowercase), sizeof(char)),
    lowercase,
    sep
    );
  char *unique = TA_filter_unique_words(
    calloc(strlen(all_words), sizeof(char)),
    all_words,
    sep
    );

  int nwords = TA_count_words(unique, sep);
  fprintf(stderr, "nwords: %d\n", nwords);

  wordmap *map = wordmap_construct(
    calloc(nwords, sizeof(wordmap)),
    all_words,
    sep,
    nwords
    );

  qsort(map, map->mapsize, sizeof(wordmap), compare_word_frequency);

  for (int j = map->mapsize - 1; j >= 0; j--)
    printf("%s %d\n", map[j].word, map[j].frequency);

  free(text);
  free(all_words);
  free(lowercase);
  free(unique);
  wordmap_free(map);

  return 0;
}
