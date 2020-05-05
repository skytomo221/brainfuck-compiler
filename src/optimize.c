#include <math.h>

#include "compiler.h"

void optimize_1() {
  int i, j;
  for (i = 0; strcmp(code[i].op, OP_END); i++) {
    j = i;
    if (!strcmp(code[j].op, OP_PLUS) || !strcmp(code[j].op, OP_MINUS)) {
      j++;
      if (strcmp(code[j].op, OP_PLUS) && strcmp(code[j].op, OP_MINUS)) continue;
      if (!strcmp(code[i].op, OP_MINUS)) {
        strcpy(code[i].op, OP_PLUS);
        code[i].diff *= -1;
      }
      while (!strcmp(code[j].op, OP_PLUS) || !strcmp(code[j].op, OP_MINUS)) {
        if (!strcmp(code[j].op, OP_PLUS)) {
          (code[i].diff)++;
        } else {
          (code[i].diff)--;
        }
        j++;
      }
      if (code[i].diff < 0) {
        strcpy(code[i].op, OP_MINUS);
      } else {
        strcpy(code[i].op, OP_PLUS);
      }
      code[i].diff = abs(code[i].diff);
      delete_from_to(i + 1, j - 1);
    }
    j = i;
    if (!strcmp(code[j].op, OP_NEXT) || !strcmp(code[j].op, OP_PREVIOUS)) {
      j++;
      if (strcmp(code[j].op, OP_NEXT) && strcmp(code[j].op, OP_PREVIOUS))
        continue;
      if (!strcmp(code[i].op, OP_PREVIOUS)) {
        strcpy(code[i].op, OP_NEXT);
        code[i].diff *= -1;
      }
      while (!strcmp(code[j].op, OP_NEXT) || !strcmp(code[j].op, OP_PREVIOUS)) {
        if (!strcmp(code[j].op, OP_NEXT)) {
          (code[i].diff)++;
        } else {
          (code[i].diff)--;
        }
        j++;
      }
      if (code[i].diff < 0) {
        strcpy(code[i].op, OP_PREVIOUS);
      } else {
        strcpy(code[i].op, OP_NEXT);
      }
      code[i].diff = abs(code[i].diff);
      delete_from_to(i + 1, j - 1);
    }
  }
}

void optimize() { optimize_1(); }
