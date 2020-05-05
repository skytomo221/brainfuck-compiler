
int load(FILE *fp) {
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
  strcpy(code[i].op, OP_END);
  for (i = 0; strcmp(code[i].op, OP_END); i++) {
    printf("%s\t%d\n", code[i].op, code[i].diff);
  }
  fclose(fp);
  puts("");
  return EXIT_SUCCESS;
}
