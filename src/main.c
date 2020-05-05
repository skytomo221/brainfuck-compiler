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
  char file[256];
  char s[256];

  if (argc > 1) {
    while (i < argc) {
      if (load(fopen(argv[i], "r")) == EXIT_FAILURE) {
        fprintf(stderr, "error: failed to read file %s\n", argv[i]);
      } else {
        strncpy(file, argv[i], strlen(argv[i]) - 3);
        file[strlen(argv[i]) - 3] = '\0';
        sprintf(s, "%s.c", file);
        gencode(fopen(s, "w"));
        sprintf(s, "gcc -std=gnu11 -O2 -DONLINE_JUDGE -o %s.out %s.c -lm", file,
                file);
        system(s);
        sprintf(s, "rm %s.c", file);
        system(s);
      }
      i++;
    }
  }
  return EXIT_SUCCESS;
}
