
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* YACC header will be in the upper level */
#include "../y.tab.h"

void print_usage() {
  printf("Usage: kuma [options]\n");
  printf("-v verbose output\n");
}

int main(int argc, char *argv[]) {
  extern int yyparse();
  extern FILE *yyin;
  // set debug mode
  extern int yydebug;

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

  yyin = stdin; 
  if (yyparse()) {
    fprintf(stderr, "ERROR!\n");
    exit(1);
  }
}
