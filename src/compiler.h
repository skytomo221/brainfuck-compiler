
#ifndef COMPILER_H
#define COMPILER_H

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
#define OP_END "end"

/* Brainfuck source code */
typedef struct Code {
  char op[16];
  int diff;
} Code;

Code code[CODE_MAX_SIZE];

void delete_from_to(int start, int end) {
  int i;
  for (i = start;; i++) {
    code[i] = code[i + end - start + 1];
    if (!strcmp(code[i].op, OP_END)) break;
  }
}

#endif
