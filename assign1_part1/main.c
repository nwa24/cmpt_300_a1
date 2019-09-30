/*
About this program:
- This program counts words.
- The specific words that will be counted are passed in as command-line
  arguments.
- The program reads words (one word per line) from standard input until EOF or
  an input line starting with a dot '.'
- The program prints out a summary of the number of times each word has
  appeared.
- Various command-line options alter the behavior of the program.

E.g., count the number of times 'cat', 'nap' or 'dog' appears.
> ./main cat nap dog
Given input:
 cat
 .
Expected output:
 Looking for 3 words
 Result:
 cat:1
 nap:0
 dog:0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smp0_tests.h"

#define LENGTH(s) (sizeof(s) / sizeof(*s))

FILE *output_file;

/* Structures */

typedef struct {
  char *word;
  int counter;
} WordCountEntry; // WordCountEntry structure

// compares the input to the words specified in the command-line argument
int process_stream(WordCountEntry entries[], int entry_count)
{
  short line_count = 0;
  char buffer[30];
  char *token_array[30];

  while (fgets(buffer, sizeof(buffer), stdin)) {
    if (*buffer == '.')
      break;
    /* Compare against each entry */
    int i = 0;
    buffer[strcspn(buffer, "\r\n")] = 0; // When using fgets it has a newline (\n) character at the end. This is done to remove it

    /* Getting all the tokens in a command line and inserting it into an array for comparison later*/
    int j = 0;
    int count_token = 0; // counting the number of words in one line
    char *token = strtok (buffer, " "); // first token

    while (token != NULL) {
      count_token++;
      token_array[j++] = token;
      token = strtok(NULL, " ");
    }

    /* Comparing each token against each entry */
    while (i < entry_count) {
      for (int k = 0; k < count_token; k++) {
        if (!strcmp(entries[i].word, token_array[k])) {
          entries[i].counter++;
        }
      }
      i++;
    }
    line_count++;
  }
  return line_count;
}

// printing the results of comparing
void print_result(WordCountEntry entries[], int entry_count)
{
  printf("Result:\n");

  // Fixed code for printing results
  for (int j = 1; j < entry_count; j++) {
    printf("%s:%d\n", entries[j].word, entries[j].counter);
  }
}

void printHelp(const char *name)
{
  fprintf(stderr, "usage: %s [-h] <word1> ... <wordN>\n", name);
}


/* MAIN FUNCTION */
int main(int argc, char **argv)
{
  const char *prog_name = *argv; // pointer for the program name

  WordCountEntry *entries = malloc(sizeof(WordCountEntry) * argc);
  int entryCount = 0;

  /* Entry point for the testrunner program */
  if (argc > 1 && !strcmp(argv[1], "-test")) {
    run_smp0_tests(argc - 1, argv + 1);
    return EXIT_SUCCESS;
  }

  while (*argv != NULL) {
    if (**argv == '-') {

      switch ((*argv)[1]) { // Checks the second argument since the first argument is always the filename
        case 'h':
          printHelp(prog_name);
          return EXIT_FAILURE; // Added: To exit out of the program completely

        case 'f':
        {
        
          char *filename = (strstr (*argv, "f"))+1;
          output_file = freopen(filename, "w", stdout);
          break;
        }
        default:
          fprintf(stderr, "%s: Invalid option %s. Use -h for help.\n",
                 prog_name, *argv);
          fprintf(stderr, "%s: Please supply at least one word. Use -h for help.\n",
                 prog_name );  
          return EXIT_FAILURE; // Added: To exit out of the program completely
      }
    } else {
      if (entryCount < argc) { // entering the entries into the WordCountEntry object
        entries[entryCount].word = *argv;
        entries[entryCount++].counter = 0;
      }
    }
    argv++;
  }
  if (entryCount == 1) { // If there were no words as input
    fprintf(stderr, "%s: Please supply at least one word. Use -h for help.\n",
           prog_name );
    return EXIT_FAILURE;
  }
  if (entryCount == 2) { // if the # of inputs=1
    printf("Looking for a single word\n");
  } else {
    printf("Looking for %d words\n", (entryCount-1));
  }

  process_stream(entries, entryCount); // compares the inputted words to the command-line argument words
  print_result(entries, entryCount);
  fclose(output_file);
  

  return EXIT_SUCCESS;
}
