
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
  int locate;
  int loop;
} Code;

Code code[CODE_MAX_SIZE];

void print_code() {
  int i;
  for (i = 0; strcmp(code[i].op, OP_END); i++) {
    if (!strcmp(code[i].op, OP_LOOP_START) ||
        !strcmp(code[i].op, OP_LOOP_END)) {
      printf("%s\t%d\tloop: %d\n", code[i].op, code[i].diff, code[i].loop);
    } else {
      printf("%s\t%d\n", code[i].op, code[i].diff);
    }
  }
}

void delete_from_to(int start, int end) {
  int i;
  for (i = start;; i++) {
    code[i] = code[i + end - start + 1];
    if (!strcmp(code[i].op, OP_END)) break;
  }
}

int look_up_loop_1(int i) {
  int start, end;
  if (!strcmp(code[i].op, OP_END)) return i;
  start = i++;
  for (; strcmp(code[i].op, OP_END); i++) {
    if (!strcmp(code[i].op, OP_LOOP_START)) {
      i = look_up_loop_1(i);
      if (!strcmp(code[i].op, OP_END)) return i;
      continue;
    } else if (!strcmp(code[i].op, OP_LOOP_END)) {
      end = i;
      code[start].loop = end;
      code[end].loop = start;
      return i;
    }
  }
  return i;
}

void look_up_loop() {
  int i = 0;
  while (strcmp(code[i = look_up_loop_1(i)].op, OP_END)) {
    while (strcmp(code[i].op, OP_LOOP_START) && strcmp(code[i].op, OP_END)) i++;
  }
}

#endif
