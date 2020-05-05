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

void optimize_2() {
  int i;
  if (strcmp(code[0].op, OP_END) && strcmp(code[1].op, OP_END) &&
      strcmp(code[2].op, OP_END))
    for (i = 2; strcmp(code[i].op, OP_END); i++) {
      if (!strcmp(code[i - 2].op, OP_LOOP_START) &&
          !strcmp(code[i - 1].op, OP_MINUS) &&
          !strcmp(code[i].op, OP_LOOP_END)) {
        if (!strcmp(code[i + 1].op, OP_PLUS)) {
          strcpy(code[i + 1].op, OP_ASSIGNMENT);
          code[i + 1].diff = code[i + 1].diff;
          delete_from_to(i - 2, i);
          i -= 3;
        } else if (!strcmp(code[i + 1].op, OP_MINUS)) {
          strcpy(code[i + 1].op, OP_ASSIGNMENT);
          code[i + 1].diff = -code[i + 1].diff;
          delete_from_to(i - 2, i);
          i -= 3;
        } else {
          delete_from_to(i - 2, i - 1);
          i -= 2;
          strcpy(code[i].op, OP_ASSIGNMENT);
          code[i].diff = 0;
        }
      }
    }
}

void optimize() {
  optimize_1();
  look_up_loop();
  optimize_2();
  look_up_loop();
}
