
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_analysis.c"

// TODO: write actual tests with assertions

int main (int argc, char *argv[])
{
  char *HELLO = "SDfAsDF10101 HELqweqL1221O 1212 ThE THE sdfasdf tHe";
  char *hello = TA_to_lowercase(calloc(strlen(HELLO), sizeof(char)), HELLO);
  printf("\ntext, original and lowercase:\n\t%s\n\t%s\n", HELLO, hello);

  char *words = TA_extract_words(calloc(strlen(hello), sizeof(char)), hello, '-');
  printf("\nextracted words: %s\n", words);

  char *unique = TA_filter_unique_words(calloc(strlen(words), sizeof(char)),
                                        words, '-');
  printf("\nfiltered words: %s\n", unique);

  int nwords = TA_count_words(unique, '-');
  printf("\nnumber of unique words: %d\n", nwords);

  wordmap *map = wordmap_construct(calloc(nwords, sizeof(wordmap)),
                                   words, '-', nwords);

  printf("\nfrequency map of extracted words:\n");

  for (wordmap *m = map; m - map < map->mapsize; m++)
    printf("\t%s: %d\n", m->word, m->frequency);

  printf("\nfrequency of 'the': %d\n", wordmap_get_frequency(map, "the"));
  printf("frequency of 'quux': %d\n", wordmap_get_frequency(map, "quux"));

  free(hello);
  free(words);
  free(unique);
  wordmap_free(map);

  return 0;
}
