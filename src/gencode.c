#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"

char head[] =
    "#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n\nint "
    "main(void)\n{\n    uint8_t tape[524288] = {0};\n    uint8_t* ptr = "
    "tape;\n";
char tail[] = "\n    return 0;\n}\n";

int gencode(FILE *fp) {
  int i, tab = 1;
  Code *code = code_list->head;
  if (fp == NULL) return EXIT_FAILURE;
  fputs(head, fp);
  while (code != NULL) {
    if (!strcmp(code->op, OP_LOOP_END)) tab--;
    for (i = 0; i < tab; i++) {
      fputs("    ", fp);
    }
    if (!strcmp(code->op, OP_PLUS)) {
      if (code->diff == 1) {
        fprintf(fp, "(*ptr)++;");
      } else {
        fprintf(fp, "(*ptr) += %d;", code->diff);
      }
    } else if (!strcmp(code->op, OP_MINUS)) {
      if (code->diff == 1) {
        fprintf(fp, "(*ptr)--;");
      } else {
        fprintf(fp, "(*ptr) -= %d;", code->diff);
      }
    } else if (!strcmp(code->op, OP_PREVIOUS)) {
      if (code->diff == 1) {
        fprintf(fp, "ptr--;");
      } else {
        fprintf(fp, "ptr -= %d;", code->diff);
      }
    } else if (!strcmp(code->op, OP_NEXT)) {
      if (code->diff == 1) {
        fprintf(fp, "ptr++;");
      } else {
        fprintf(fp, "ptr += %d;", code->diff);
      }
    } else if (!strcmp(code->op, OP_OUTPUT)) {
      fprintf(fp, "putchar(*ptr);");
    } else if (!strcmp(code->op, OP_INPUT)) {
      fprintf(fp, "*ptr = getchar();");
    } else if (!strcmp(code->op, OP_LOOP_START)) {
      tab++;
      fprintf(fp, "while (*ptr) {");
    } else if (!strcmp(code->op, OP_LOOP_END)) {
      fprintf(fp, "}");
    } else if (!strcmp(code->op, OP_ASSIGNMENT)) {
      fprintf(fp, "(*ptr) = %d;", code->diff);
    } else if (!strcmp(code->op, OP_PUTCHAR)) {
      switch (code->diff) {
        case '\n':
          fputs("putchar('\\n');", fp);
          break;
        case '\t':
          fputs("putchar('\\t');", fp);
          break;
        default:
          fprintf(fp, "putchar('%c');", code->diff);
          break;
      }
    }
    fputs("\n", fp);
    code = code->next;
  }
  fputs(tail, fp);
  fclose(fp);
  return EXIT_SUCCESS;
}
