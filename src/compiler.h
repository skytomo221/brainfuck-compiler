
#ifndef COMPILER_H
#define COMPILER_H

/* AtCoder 512 KiB */
#define CODE_MAX_SIZE 262144
/* I want to set 524288 but it caused out of memory. So, it is 262144 */

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

void replace(Code *old, Code *new) {
  puts("OK");
  int i;
  for (i = 0;; i++) {
    old[i] = new[i];
    if (!strcmp(new[i].op, OP_END)) break;
  }
}

#endif
