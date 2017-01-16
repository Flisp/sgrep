#ifndef SGREP_DATA_H
#define SGREP_DATA_H

typedef struct sgrep_data_ {
  char *search_string;
  char *filename;
  enum { SENSITIVE, INSENSITIVE } case_insensitive;
  enum { NORMAL, ROW_NUMBER, COUNT } display_mode;
} sgrep_data;

typedef enum {
    SUCCESS,
    TOO_MANY_ARGUMENTS,
    ARGUMENTS_MISSING
} error_code;

typedef enum {
  FOUND,
  NOT_FOUND,
  FATAL_ERROR
} exit_code;

#endif /* SGREP_DATA_H */
