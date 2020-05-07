#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"

int load(FILE *fp) {
  int c;
  Code new_code;
  CodeList *new_code_list;

  new_code_list = code_list_init();

  new_code.diff = 1;

  if (fp == NULL) return EXIT_FAILURE;
  while ((c = fgetc(fp)) != EOF) {
    switch (c) {
      case TOKEN_PLUS:
        strcpy(new_code.op, OP_PLUS);
        code_list_add(new_code_list, new_code);
        break;
      case TOKEN_MINUS:
        strcpy(new_code.op, OP_MINUS);
        code_list_add(new_code_list, new_code);
        break;
      case TOKEN_PREVIOUS:
        strcpy(new_code.op, OP_PREVIOUS);
        code_list_add(new_code_list, new_code);
        break;
      case TOKEN_NEXT:
        strcpy(new_code.op, OP_NEXT);
        code_list_add(new_code_list, new_code);
        break;
      case TOKEN_OUTPUT:
        strcpy(new_code.op, OP_OUTPUT);
        code_list_add(new_code_list, new_code);
        break;
      case TOKEN_INPUT:
        strcpy(new_code.op, OP_INPUT);
        code_list_add(new_code_list, new_code);
        break;
      case TOKEN_LOOP_START:
        strcpy(new_code.op, OP_LOOP_START);
        code_list_add(new_code_list, new_code);
        break;
      case TOKEN_LOOP_END:
        strcpy(new_code.op, OP_LOOP_END);
        code_list_add(new_code_list, new_code);
        break;
      default:
        continue;
    }
  }
  code_list = new_code_list;
  code_list_look_up_loop(code_list);
  fclose(fp);
  return EXIT_SUCCESS;
}
