
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
#define OP_ASSIGNMENT "="
#define OP_PUTCHAR "putchar"

/* Brainfuck source code */
typedef struct Code {
  char op[8];
  int diff;
  int locate;
  struct Code *loop;
  struct Code *next;
} Code;

Code code[CODE_MAX_SIZE];

void print_code() {
  int i;
  for (i = 0; strcmp(code[i].op, OP_END); i++) {
    if (!strcmp(code[i].op, OP_LOOP_START) ||
        !strcmp(code[i].op, OP_LOOP_END)) {
      printf("%s\t%d\n", code[i].op, code[i].diff);
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

typedef struct CodeList {
  Code *head;
  Code *tail;
  int count;
  int tape_size;
} CodeList;

CodeList *code_list;

CodeList *code_list_init() {
  CodeList *new_code_list;
  Code *head_code;
  new_code_list = (CodeList *)malloc(sizeof(CodeList));
  head_code = (Code *)malloc(sizeof(Code));
  new_code_list->head = head_code;
  new_code_list->tail = head_code;
  new_code_list->count = 1;
  new_code_list->tape_size = 1;
  head_code->next = NULL;
  return new_code_list;
}

int code_list_count_tape_size(CodeList *code_list) {
  int cnt = 1, max_cnt = 1;
  Code *code = code_list->head;
  while (code != NULL) {
    if (!strcmp(code->op, OP_NEXT)) {
      cnt++;
      if (max_cnt < cnt) max_cnt = cnt;
    } else if (!strcmp(code->op, OP_PREVIOUS)) {
      cnt--;
    }
    code = code->next;
  }
  return code_list->tape_size = max_cnt;
}

void code_check(CodeList *code_list) {
  int cnt = 0;
  Code *code = code_list->head;
  while (code != NULL) {
    if (!strcmp(code->op, OP_LOOP_START)) {
      cnt++;
    } else if (!strcmp(code->op, OP_LOOP_END)) {
      cnt--;
    }
    code = code->next;
  }
  if (cnt) {
    fprintf(
        stderr,
        "brainfuck-compiler: \033[31merror:\033[39m Parentheses mismatch\n");
    exit(EXIT_FAILURE);
  }
}

CodeList *code_list_look_up_loop(CodeList *code_list) {
  Code *code_loop_start = code_list->head;
  Code *code_loop_end;
  code_check(code_list);
  while (code_loop_start != NULL) {
    if (!strcmp(code_loop_start->op, OP_LOOP_START)) {
      code_loop_end = code_loop_start->next;
      while (code_loop_end != NULL) {
        if (!strcmp(code_loop_end->op, OP_LOOP_END)) {
          code_loop_start->loop = code_loop_end;
          code_loop_end->loop = code_loop_start;
          break;
        }
        code_loop_end = code_loop_end->next;
      }
    }
    code_loop_start = code_loop_start->next;
  }
  return code_list;
}

CodeList *code_list_add(CodeList *code_list, Code next) {
  Code *next_code;
  next_code = (Code *)malloc(sizeof(Code));
  *next_code = next;
  code_list->tail = code_list->tail->next = next_code;
  code_list->tail->next = NULL;
  code_list->count++;
  code_list_count_tape_size(code_list);
  return code_list;
}

void *code_list_print(CodeList *code_list) {
  Code *code = code_list->head;
  printf("code size: %d\n", code_list->count);
  printf("tape size: %d\n", code_list->tape_size);
  while (code != NULL) {
    printf("%s\t%d\n", code->op, code->diff);
    code = code->next;
  }
}

#endif
