#ifndef SEARCHER_H
#define SEARCHER_H
#include "sgrep_data.h"

typedef enum {
  NO_MATCH,
  MATCH
} search_result;

#define SIZE_INPUT 1000

search_result search_string(char *indata, sgrep_data* grep_data);
exit_code search_input(sgrep_data *grep_data);

#endif /* SEARCHER_H */
