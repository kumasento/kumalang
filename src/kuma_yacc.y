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
%token ADD SUB MUL DIV CR LPAREN RPAREN
%type <double_value> expr term factor
%%
line_list
  : line
  | line_list line
  ;
line
  : expr CR 
  { printf("= %lf \n", $1); }
  ;
expr
  : expr ADD term 
  { $$ = $1 + $3; }
  | expr SUB term 
  { $$ = $1 - $3; }
  | term 
  { $$ = $1; }
  ;
term
  : term MUL factor 
  { $$ = $1 * $3; }
  | term DIV factor 
  { $$ = $1 / $3; }
  | factor
  { $$ = $1; }
  ;
factor
  : DOUBLE_LITERAL
  { $$ = $1; }
  | LPAREN expr RPAREN
  { $$ = $2; }
  | SUB factor
  { $$ = -$2; }
  ;
%%
int yyerror(char const *str) {
  extern char *yytext;
  fprintf(stderr, "parser error near %s\n", yytext);
  return 0;
}

