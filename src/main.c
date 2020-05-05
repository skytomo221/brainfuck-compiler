#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* AtCoder 512 KiB */
#define CODE_MAX_SIZE 524288

#define TOKEN_PLUS '+'
#define TOKEN_MINUS '-'
#define TOKEN_PREVIOUS '<'
#define TOKEN_NEXT '>'
#define TOKEN_OUTPUT '.'
#define TOKEN_INPUT ','
#define TOKEN_LOOP_START '['
#define TOKEN_LOOP_END ']'

#define OP_PLUS "+"
#define OP_MINUS "-"
#define OP_PREVIOUS "<"
#define OP_NEXT ">"
#define OP_OUTPUT "."
#define OP_INPUT ","
#define OP_LOOP_START "["
#define OP_LOOP_END "]"

/* Brainfuck source code */
typedef struct Code {
  char op[16];
  int diff;
} Code;

Code code[CODE_MAX_SIZE];

char head[] =
    "#include <stdio.h>\n\
#include <stdint.h>\n\
#include <stdlib.h>\n\
\n\
int main(void)\n\
{\n\
    uint8_t mem[30000] = {0};\n\
    uint8_t* ptr = mem;\n";
char tail[] = "}\n";

int read_bf_file(FILE *fp) {
  int i = 0;
  int c;

  if (fp == NULL) return EXIT_FAILURE;
  while ((c = fgetc(fp)) != EOF) {
    switch (c) {
      case TOKEN_PLUS:
        strcpy(code[i].op, OP_PLUS);
        break;
      case TOKEN_MINUS:
        strcpy(code[i].op, OP_MINUS);
        break;
      case TOKEN_PREVIOUS:
        strcpy(code[i].op, OP_PREVIOUS);
        break;
      case TOKEN_NEXT:
        strcpy(code[i].op, OP_NEXT);
        break;
      case TOKEN_OUTPUT:
        strcpy(code[i].op, OP_OUTPUT);
        break;
      case TOKEN_INPUT:
        strcpy(code[i].op, OP_INPUT);
        break;
      case TOKEN_LOOP_START:
        strcpy(code[i].op, OP_LOOP_START);
        break;
      case TOKEN_LOOP_END:
        strcpy(code[i].op, OP_LOOP_END);
        break;
      default:
        continue;
    }
    code[i].diff = 1;
    i++;
  }
  strcpy(code[i].op, "END");
  for (i = 0; strcmp(code[i].op, "END"); i++) {
    printf("%s\t%d\n", code[i].op, code[i].diff);
  }
  fclose(fp);
  puts("");
  return EXIT_SUCCESS;
}

int gencode(FILE *fp) {
  int i = 0;
  if (fp == NULL) return EXIT_FAILURE;
  fputs(head, fp);
  for (i = 0; strcmp(code[i].op, "END"); i++) {
    fputs("\t", fp);
    printf("OK : %s\n", code[i].op);
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

int main(int argc, char *argv[]) {
  int c;
  int i = 1;
  int option_index = 0;

  if (argc > 1) {
    while (i < argc)
      if (read_bf_file(fopen(argv[i++], "r")) == EXIT_FAILURE) {
        fprintf(stderr, "error: failed to read file %s\n", argv[i - 1]);
      } else {
        gencode(fopen("output.c", "w"));
      }
  }
  return EXIT_SUCCESS;
}
