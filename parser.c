#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "sgrep_data.h"

/* sgrep Kajsa
   sgrep Kajsa filnamn.txt
   sgrep -i Kajsa
   sgrep -i Kajsa filnamn.txt
   sgrep -n -i Kajsa 
   sgrep -c Kajsa 
   sgrep -i -n Kajsa filnamn
   sgrep -c -i Kajsa filnamn
   argv[0] = "sgrep"
   argv[1] = "-c"
   argv[2] = "-i"
   argv[3] = "Kajsa"
   argv[4] = "filnamn"
*/

error_code parse_arguments(int argc, char *argv[], sgrep_data *data)
{
  int i;

  data->search_string = NULL;         /* no data yet */
  data->filename = NULL;              /* no data yet */
  data->case_insensitive = SENSITIVE; /* default mode */
  data->display_mode = NORMAL;        /* default mode */

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0) {
      data->case_insensitive = INSENSITIVE;
    }
    else if (strcmp(argv[i], "-n") == 0) {
      data->display_mode = ROW_NUMBER;
    }
    else if (strcmp(argv[i], "-c") == 0) {
      data->display_mode = COUNT;
    }
    else if (data->search_string == NULL) {
      data->search_string = argv[i];
    }
    else if (data->filename == NULL) {
      data->filename = argv[i];
    }
    else {
      return TOO_MANY_ARGUMENTS;
    }
  }

  /* search string was not found in the loop */
  if (data->search_string == NULL) {
    return ARGUMENTS_MISSING;
  }
  
  return SUCCESS;
}


