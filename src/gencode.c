#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"

char head[] =
    "#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n\nint "
    "main(void)\n{\n    uint8_t mem[524288] = {0};\n    uint8_t* ptr = mem;\n";
char tail[] = "}\n";

int gencode(FILE *fp) {
  int i, j;
  int tab = 1;
  if (fp == NULL) return EXIT_FAILURE;
  fputs(head, fp);
  for (i = 0; strcmp(code[i].op, OP_END); i++) {
    if (!strcmp(code[i].op, OP_LOOP_END)) tab--;
    for (j = 0; j < tab; j++) {
      fputs("    ", fp);
    }
    if (!strcmp(code[i].op, OP_PLUS)) {
      fprintf(fp, "(*ptr)++;");
    } else if (!strcmp(code[i].op, OP_MINUS)) {
      fprintf(fp, "(*ptr)--;");
    } else if (!strcmp(code[i].op, OP_PREVIOUS)) {
      fprintf(fp, "ptr--;");
    } else if (!strcmp(code[i].op, OP_NEXT)) {
      fprintf(fp, "ptr++;");
    } else if (!strcmp(code[i].op, OP_OUTPUT)) {
      fprintf(fp, "putchar(*ptr);");
    } else if (!strcmp(code[i].op, OP_INPUT)) {
      fprintf(fp, "*ptr = getchar();");
    } else if (!strcmp(code[i].op, OP_LOOP_START)) {
      tab++;
      fprintf(fp, "while (*ptr) {");
    } else if (!strcmp(code[i].op, OP_LOOP_END)) {
      fprintf(fp, "}");
    }
    fputs("\n", fp);
  }
  fputs(tail, fp);
  fclose(fp);
  return EXIT_SUCCESS;
}
