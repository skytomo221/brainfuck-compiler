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
      if (code[i].diff == 1) {
        fprintf(fp, "(*ptr)++;");
      } else {
        fprintf(fp, "(*ptr) += %d;", code[i].diff);
      }
    } else if (!strcmp(code[i].op, OP_MINUS)) {
      if (code[i].diff == 1) {
        fprintf(fp, "(*ptr)--;");
      } else {
        fprintf(fp, "(*ptr) -= %d;", code[i].diff);
      }
    } else if (!strcmp(code[i].op, OP_PREVIOUS)) {
      if (code[i].diff == 1) {
        fprintf(fp, "ptr--;");
      } else {
        fprintf(fp, "ptr -= %d;", code[i].diff);
      }
    } else if (!strcmp(code[i].op, OP_NEXT)) {
      if (code[i].diff == 1) {
        fprintf(fp, "ptr++;");
      } else {
        fprintf(fp, "ptr += %d;", code[i].diff);
      }
    } else if (!strcmp(code[i].op, OP_OUTPUT)) {
      fprintf(fp, "putchar(*ptr);");
    } else if (!strcmp(code[i].op, OP_INPUT)) {
      fprintf(fp, "*ptr = getchar();");
    } else if (!strcmp(code[i].op, OP_LOOP_START)) {
      tab++;
      fprintf(fp, "while (*ptr) {");
    } else if (!strcmp(code[i].op, OP_LOOP_END)) {
      fprintf(fp, "}");
    } else if (!strcmp(code[i].op, OP_ASSIGNMENT)) {
      fprintf(fp, "(*ptr) = %d;", code[i].diff);
    }
    fputs("\n", fp);
  }
  fputs(tail, fp);
  fclose(fp);
  return EXIT_SUCCESS;
}
