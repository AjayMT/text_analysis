
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

  int nwords = TA_count_words(all_words, sep);

  wordmap *map = wordmap_construct(
    calloc(nwords, sizeof(wordmap)),
    all_words,
    sep,
    nwords
    );

  wordmap *consolidated = wordmap_consolidate(
    calloc(nwords, sizeof(wordmap)),
    map
    );

  fprintf(stderr, "mapsize: %d\n", consolidated->mapsize);

  qsort(
    consolidated,
    consolidated->mapsize,
    sizeof(wordmap),
    compare_word_frequency
    );

  for (int j = consolidated->mapsize - 1; j >= 0; j--)
    printf("%s %d\n", consolidated[j].word, consolidated[j].frequency);

  free(text);
  free(all_words);
  free(lowercase);
  wordmap_free(consolidated);
  wordmap_free(map);

  return 0;
}
