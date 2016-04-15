
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* YACC header will be in the upper level */
#include "kuma_ast.h"
#include "kuma_interpreter.h"
#include "../y.tab.h"

void print_usage() {
  printf("Usage: kuma [options]\n");
  printf("-v verbose output\n");
}

void print_info() {
  printf("\x1b[35m熊ランコンパイラ\x1b[0m\n");
  printf("\x1b[33mVersion:\x1b[0m 0.1.0\n");
  printf("\x1b[33mAuthor:\x1b[0m  Vincent Zhao <vincentzhaorz@gmail.com>\n");
  printf("\n");
}

int main(int argc, char *argv[]) {
  extern int yyparse();
  extern FILE *yyin;
  // set debug mode
  extern int yydebug;

  print_info();

  int c;
  while ((c = getopt(argc, argv, "vh")) != -1) {
    switch (c) {
      case 'v':
        yydebug = 1;
        break;
      case 'h':
        print_usage();
        return 0;
      default:
        fprintf(stderr, "Unrecognised char: %c\n", c);
        print_usage();
        exit(1);
    }
  }
  // initial print
  printf("=> ");
  yyin = stdin; 
  if (yyparse()) {
    fprintf(stderr, "ERROR!\n");
    exit(1);
  }
}
