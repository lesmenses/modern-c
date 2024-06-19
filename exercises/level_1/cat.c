#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

enum { buf_max = 32, };

int main(int argc, char* argv[argc+1]) {
  int ret = EXIT_FAILURE;
  char buffer[buf_max] = { 0 };
  bool is_line_number_output = false;
  if(argc > 1 && strcmp(argv[0], "-n")) {
    is_line_number_output = true;
  }

  // Exs 54. Ctrl-D sends EOF in bash.
  if((is_line_number_output && argc == 2) || (!is_line_number_output && argc == 1)) {
      size_t line_number = 0;
      while(fgets(buffer, buf_max, stdin)) {
        fprintf(stdout, "%zu: ", line_number);
        fputs(buffer, stdout);
        ++line_number;
      }
      return EXIT_SUCCESS;
  }

  for (int i = is_line_number_output ? 2 : 1; i < argc; ++i) {        // Processes args
    FILE* instream = fopen(argv[i], "r"); // as filenames
    if (instream) {
    size_t line_number = 0;
    while (fgets(buffer, buf_max, instream)) {
        fprintf(stdout, "%zu: ", line_number);
        fputs(buffer, stdout);
        ++line_number;
    }
    fclose(instream);
    ret = EXIT_SUCCESS;
    } else {
    /* Provides some error diagnostic. */
    fprintf(stderr, "Could not open %s: ", argv[i]);
    perror(0);
    errno = 0;                       // Resets the error code
    }
  }
  return ret;
}
