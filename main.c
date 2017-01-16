#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "searcher.h"
#include "sgrep_data.h"

static void handle_error(error_code failure)
{
  if (failure == TOO_MANY_ARGUMENTS) {
    fprintf(stderr, "Too many arguments\n");
    exit((int)FATAL_ERROR);
  }
  else if (failure == ARGUMENTS_MISSING) {
    fprintf(stderr, "Arguments missing\n");
    exit((int)FATAL_ERROR);
  }
}


int main(int argc, char *argv[])
{
  sgrep_data grep_data;
  error_code result;
  
  result = parse_arguments(argc, argv, &grep_data);
  
  if (result == SUCCESS) {
    return search_input(&grep_data);
  }
  else {
    handle_error(result);
  }

  return 0;
}
