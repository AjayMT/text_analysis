
#ifndef TEXT_ANALYSIS_C
#define TEXT_ANALYSIS_C

// text_analysis.c
//
// This file provides various functions that operate on strings of text
// and 'wordmaps', which are essentially hash tables that map words in
// a body of text to their frequency of occurrence.
//
// This project was inspired by Jason Xia's 'TextAnalyzer'
// https://github.com/jasonxia17/TextAnalyzer

// The #ifndef and #endif preprocessor statements at the top and bottom of
// the file ensure that it is only imported once, even when
// #include "text_analysis.c"
// appears multiple times in a project.

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The 'boolean' type does not exist in C, conditional statements use
// integers instead.
// The #define statements below tell the preprocessor to replace all
// occurrences of 'true' with '1' and 'false' with '0'.
#define true 1
#define false 0

// 'typedef' statements define new types from existing primitives.
// For example, if I wanted to define a 'string' type as an array of characters,
// I would write:
// typedef char[] string;
//
// In this case, I am defining a 'wordmap' type as a 'struct'.
// 'structs' are essentially bundles of state, i.e collections of variables.
// Each wordmap struct is essentially a word-frequency pair that is part
// of a 'hash table' of words and frequencies.
//
// char *word is the word of a particular 'entry' in the 'hash table'
// int frequency is the frequency of the word contained in wordmap.word
// int mapsize is the total number of words in the 'hash table'
//   (mapsize is really only a part of the struct to simplify operations on
//    wordmaps. Unlike Java, C arrays do not know how big they are.)
typedef struct {
  char *word;
  int frequency;
  int mapsize;
} wordmap;

// C has no concept of 'file' or 'package' scope, so to avoid naming
// conflicts, I have to prefix all of my functions with 'TA' or 'wordmap'
// and hope that they are unique.
//
// I am declaring all of my functions before implementing them.
// This allows me to call every function from every other function without
// causing 'undefined symbol' errors.
int TA_streq (char *a, char *b);
char *TA_to_lowercase (char *dst, char *string);
char *TA_extract_words (char *dst, char *string, char sep);
int TA_count_words (char *string, char sep);
char *TA_filter_unique_words (char *dst, char *string, char sep);
wordmap *wordmap_construct (wordmap *map, char *string, char sep, int nwords);
int wordmap_get_frequency (wordmap *map, char *word);
void wordmap_free (wordmap *map);

// The 'streq' function checks if two strings (which are just character arrays)
// are equal.
//
// char *a and char *b are the two strings to compare
int TA_streq (char *a, char *b)
{
  if (strlen(a) != strlen(b)) return false;

  // this loop enumerates through the characters in 'a' and 'b' until
  // it reaches '\0', which is the character used to terminate a string
  for (; *a != '\0'; a++, b++)
    if (*a != *b) return false;

  return true;
}

// to_lowercase converts all uppercase letters to lowercase letters in a
// given string and stores the result in another character pointer (i.e
// another reference variable).
//
// char *dst is the 'destination' pointer in which the result will be stored
// char *string is the string to operate on
// this function also returns the destination pointer
char *TA_to_lowercase (char *dst, char *string)
{
  unsigned long i;

  for (i = 0; string[i] != '\0'; i++)
    dst[i] = tolower(string[i]);

  dst[i] = '\0';

  return dst;
}

// extract_words extracts all words (all contiguous groups of alphabetical
// characters) from a given string and stores the results in a destination
// pointer. The extracted words are separated by 'sep' when stored in the
// destination pointer.
//
// char *dst is the destination pointer
// char *string is the string to operate on
// char sep is the separator character to insert between words
// this function also returns the destination pointer
char *TA_extract_words (char *dst, char *string, char sep)
{
  unsigned long dstindex = 0;

  while (*string != '\0') {
    // copy the current 'word' into dst
    for(; isalpha(*string); string++) {
      dst[dstindex] = *string;
      dstindex++;
    }

    // step forward until the next word is reached
    for(; (! isalpha(*string)) && *string != '\0'; string++);

    // insert a separator
    dst[dstindex] = sep;
    dstindex++;
  }

  dst[dstindex] = '\0';

  return dst;
}

// count_words counts the number of words in a given string, in which each
// word is separated by 'sep'.
//
// char *string is the string to count words from
// char sep is the character that separates words in 'string'
// this function returns the number of words in 'string'
int TA_count_words (char *string, char sep)
{
  int count = 0;

  for (; *string != '\0'; string++)
    if (*string == sep) count++;

  return count;
}

// filter_unique_words traverses a string and copies the first occurrence of
// each word into a destination pointer.
// This effectively removes all duplicate instances of every word in the string.
// Words in 'string' as well as the destination pointer are separated by 'sep'.
// This function uses wordmap_construct to create a list of unique words.
//
// char *dst is the destination pointer
// char *string is the unfiltered string
// char sep is the character that separates words in 'string' and 'dst'
// this function returns the destination pointer
char *TA_filter_unique_words (char *dst, char *string, char sep)
{
  wordmap *map = wordmap_construct(
    calloc(TA_count_words(string, sep), sizeof(wordmap)),
    string,
    sep,
    TA_count_words(string, sep)
    );

  int dstindex = 0;

  for (int i = 0; i < map->mapsize && map[i].word != NULL; i++) {
    for (int j = 0; map[i].word[j] != '\0'; j++) {
      dst[dstindex] = map[i].word[j];
      dstindex++;
    }

    dst[dstindex] = sep;
    dstindex++;
  }

  wordmap_free(map);

  return dst;
}

// wordmap_construct creates a 'wordmap' hash-table-like data structure
// from a given string. Each word is mapped to (i.e is in the same struct as)
// its frequency of occurrence in the string.
//
// The algorithm works as follows:
// - enumerate through words in 'string', separated by 'sep'
// - for each word, enumerate through wordmap nodes in 'map'
// - if word exists in 'map', increment its frequency
// - otherwise, insert a new word node into 'map'
//
// wordmap *map is a pointer to wordmap which will be populated
// char *string is the string to analyse
// char sep is the character that separates words in 'string'
// int nwords is the maximum number of words to insert into the wordmap
//   (the primary purpose of 'nwords' is to make memory allocation easier
//    and avoid segmentation faults)
wordmap *wordmap_construct (wordmap *map, char *string, char sep, int nwords)
{
  char *begin = string; // beginning of current word in string

  for (; *string != '\0'; string++)
    if (*string == sep) { // 'string' is at the end of a word
      int wordExists = false; // whether the word already exists in map
      wordmap *m = map; // pointer to current wordmap node
      char *currentWord = calloc(string - begin, sizeof(char)); // current word in string

      for (int i = 0; i < string - begin; i++) currentWord[i] = begin[i];

      // iterate through word nodes to find match
      for (; (m - map) < nwords && m->word != NULL; m++) {
        if (TA_streq(m->word, currentWord)) { // same word found
          m->frequency++;
          wordExists = true;
          break;
        }
      }

      if ((! wordExists) && m - map < nwords) { // word does not exist in map
        m->word = calloc(strlen(currentWord), sizeof(char));
        strcpy(m->word, currentWord);
        m->frequency = 1;
      }

      string++;
      begin = string; // shift to beginning of next word in string
      free(currentWord);
    }

  int mapsize = 0;
  for (; mapsize < nwords && map[mapsize].word != NULL; mapsize++);

  for (wordmap *m = map; (m - map) < mapsize; m++)
    m->mapsize = mapsize;

  return map;
}

// wordmap_get_frequency returns the frequency of a given word in a
// wordmap.
//
// wordmap *map is the map to search
// char *word is the word to search for
// this function returns the associated 'frequency' of 'word' in 'map'
int wordmap_get_frequency (wordmap *map, char *word)
{
  for (wordmap *m = map; (m - map) < map->mapsize; m++)
    if (TA_streq(m->word, word))
      return m->frequency;

  return 0;
}

// wordmap_free deallocates all the memory that has been allocated to store
// the contents of a particular wordmap.
// Java automatically handles memory management through a process called
// 'garbage collection' -- C forces you to do all the housekeeping yourself.
//
// wordmap *map is the map to deallocate
void wordmap_free (wordmap *map)
{
  for (int i = 0; i < map->mapsize; i++)
    free((map + i)->word);

  free(map);
}

#endif
