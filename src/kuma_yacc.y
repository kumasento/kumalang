%{
#include <stdio.h>
#include <stdlib.h>

// To enable debug verbose output
#define YYDEBUG 2

// To make compiler happy
#if YYBISON
int yyerror(const char *s);
int yylex();
#endif
%}
%union {
  int int_value;
  double double_value;
}
%token <double_value> DOUBLE_LITERAL
%token ADD SUB MUL DIV CR
%type <double_value> expr term
%%
line_list
  : line
  | line_list line
  ;
line
  : expr CR
  { printf("Result = %lf \n", $1); }
  ;
expr
  : term { $$ = $1; }
  | expr ADD term { $$ = $1 + $3; }
  | expr SUB term { $$ = $1 - $3; }
  | expr MUL term { $$ = $1 * $3; }
  | expr DIV term { $$ = $1 / $3; }
  ;
term
  : DOUBLE_LITERAL
  { $$ = $1; printf("DOUBLE_LITERAL = %lf\n", $$); }
  ;
%%
int yyerror(char const *str) {
  extern char *yytext;
  fprintf(stderr, "parser error near %s\n", yytext);
  return 0;
}

