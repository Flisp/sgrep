#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "searcher.h"

#include "sgrep_data.h"

#define TRUE 1
#define FALSE 0

search_result search_string(char *indata, sgrep_data* grep_data)
{
  /* search inside the indata string
   * If strstr or strcasestr returns NULL, search_string was not found
   */
  
  /* If user types -i use strcasestr
   * otherwise use strstr */
  if (grep_data->case_insensitive == INSENSITIVE) {
    if (strcasestr(indata, grep_data->search_string) == NULL)
      return NO_MATCH;
    else
      return MATCH;
  }
  else {
    if (strstr(indata, grep_data->search_string) == NULL)
      return NO_MATCH;
    else
      return MATCH;
  }
}

/* This is the main loop of the program. It reads stdin, line by line,
 * and searches each line for the search_string.
 */
exit_code search_input(sgrep_data *grep_data)
{
  char *current_line;
  int current_size;
  int length;
  int found = FALSE;  /* boolean */
  int end_of_input = FALSE; /* boolean */
  int end_of_line; /* boolean */
  int row = 1; /* to display row number */
  int counter = 0; /* how many times string is found */
  FILE *file;

  if (grep_data->filename == NULL) {
    /* no filename - read from stdin */
    file = stdin;
  }
  else {
    /* try to open file */
    file = fopen(grep_data->filename, "r");

    if (file == NULL) {
      fprintf(stderr, "File not found\n");
      return FATAL_ERROR;
    }
  }

  /* handle long lines with malloc realloc loop and fgets */
  while(!end_of_input) {
    current_line = malloc(SIZE_INPUT);

    if (current_line == NULL) {
      return FATAL_ERROR;
    }

    current_size = SIZE_INPUT;
    
    if (fgets(current_line, SIZE_INPUT, file) == NULL) {
      end_of_input = TRUE;
      free(current_line);
    }
    else {
      end_of_line = FALSE;

      while (!end_of_line) {
        length = strlen(current_line);

        if (current_line[length - 1] == '\n') {
          /* Last character is a line break - reached end of line */
          current_line[length - 1] = '\0';
          end_of_line = TRUE;
        }
        else {
          /* Make the buffer bigger */
          current_size = current_size + SIZE_INPUT;
          current_line = realloc(current_line, current_size);
          if (current_line == NULL) {
            return FATAL_ERROR;
          }

          if (fgets(current_line + length, current_size - length, file) == NULL) {
            /* end of file here means end of last line without line break */
            end_of_line = TRUE;
          }
        }
      }
      /* here there is definitely a text line in current_line */

      if (search_string(current_line, grep_data) == MATCH) {
        if (grep_data->display_mode == NORMAL) {
          printf("%s\n", current_line);
        }
        else if (grep_data->display_mode == ROW_NUMBER) {
          printf("%d:%s\n", row, current_line);
        }
        else if (grep_data->display_mode == COUNT) {
          counter++;
        }
        found = TRUE;
      }

      free(current_line);
    }

    row++;
  }

  if (grep_data->display_mode == COUNT) {
    printf("%d\n", counter);
  }
  
  if (file != stdin) {
    fclose(file);
  }

  /* Return FOUND or NOT_FOUND */
  if (found)
    return FOUND;
  else
    return NOT_FOUND;
}
