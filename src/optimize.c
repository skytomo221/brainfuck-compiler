#include <math.h>
#include <stdlib.h>

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

void optimize_3() {
  int i, cnt, max_cnt;
  char *tape, *ptr;
  Code *new_code, *new_code_ptr;
  for (i = cnt = max_cnt = 0; strcmp(code[i].op, OP_END); i++) {
    if (!strcmp(code[i].op, OP_INPUT)) return;
    if (!strcmp(code[i].op, OP_NEXT)) {
      cnt++;
      if (max_cnt < cnt) max_cnt = cnt;
    } else if (!strcmp(code[i].op, OP_PREVIOUS)) {
      cnt--;
    }
  }
  ptr = tape = (char *)malloc(max_cnt);
  for (i = 0; i < max_cnt; i++) {
    tape[i] = 0;
  }
  new_code_ptr = new_code =
      (Code *)malloc(sizeof(struct Code) * (CODE_MAX_SIZE / 128));
  if (tape == NULL) {
    puts("fault tape");
    return;
  }
  if (new_code == NULL) {
    puts("fault new code");
    return;
  }
  for (i = 0; strcmp(code[i].op, OP_END); i++) {
    if (!strcmp(code[i].op, OP_PLUS)) {
      (*ptr) += code[i].diff;
    } else if (!strcmp(code[i].op, OP_MINUS)) {
      (*ptr) -= code[i].diff;
    } else if (!strcmp(code[i].op, OP_PREVIOUS)) {
      ptr -= code[i].diff;
    } else if (!strcmp(code[i].op, OP_NEXT)) {
      ptr += code[i].diff;
    } else if (!strcmp(code[i].op, OP_OUTPUT)) {
      strcpy((*new_code_ptr).op, OP_PUTCHAR);
      new_code_ptr->diff = (*ptr);
      new_code_ptr++;
    } else if (!strcmp(code[i].op, OP_LOOP_START)) {
      // if ((*ptr) == 0) i = code[i].loop;
    } else if (!strcmp(code[i].op, OP_LOOP_END)) {
      // if ((*ptr) != 0) i = code[i].loop;
    } else if (!strcmp(code[i].op, OP_ASSIGNMENT)) {
      (*ptr) = code[i].diff;
    }
    /*printf("i:%d\top:%s\tdiff:%d\tptr:%lx\t(*ptr):%d\n", i, code[i].op,
           code[i].diff, ptr - tape, (*ptr));*/
  }
  strcpy(new_code_ptr->op, OP_END);
  for (i = 0; strcmp(new_code[i].op, OP_END); i++) {
    code[i] = new_code[i];
  }
  code[i] = new_code[i];
  // free(tape);
  // free(new_code);
}

void optimize() {
  optimize_1();
  // look_up_loop();
  optimize_2();
  // look_up_loop();
  // optimize_3();
  // look_up_loop();
}
