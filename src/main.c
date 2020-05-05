#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "gencode.c"
#include "load.c"

int main(int argc, char *argv[]) {
  int c;
  int i = 1;
  int option_index = 0;

  if (argc > 1) {
    while (i < argc)
      if (load(fopen(argv[i++], "r")) == EXIT_FAILURE) {
        fprintf(stderr, "error: failed to read file %s\n", argv[i - 1]);
      } else {
        gencode(fopen("output.c", "w"));
      }
  }
  return EXIT_SUCCESS;
}