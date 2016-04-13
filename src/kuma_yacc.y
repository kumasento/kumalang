%{
#include <stdio.h>
#include <stdlib.h>

#include "kuma_ast.h"

// To enable debug verbose output
#define YYDEBUG 2

// To make compiler happy
#if YYBISON
int yyerror(const char *s);
int yylex();
#endif
%}
%union {
  Expr  *expr;
}
%token <expr> DOUBLE_LITERAL
%token ADD SUB MUL DIV CR LPAREN RPAREN
%type <expr> expr term factor
%%
line_list
  : line
  | line_list line
  ;
line
  : expr CR 
  { printf("= %lf \n", ($1)->value.real); }
  ;
expr
  : expr ADD term 
  { $$ = create_binary_expr(ADD_BINARY_EXPR, $1, $3); }
  | expr SUB term 
  { $$ = create_binary_expr(SUB_BINARY_EXPR, $1, $3); }
  | term 
  { $$ = $1; }
  ;
term
  : term MUL factor 
  { $$ = create_binary_expr(MUL_BINARY_EXPR, $1, $3); }
  | term DIV factor 
  { $$ = create_binary_expr(DIV_BINARY_EXPR, $1, $3); }
  | factor
  { $$ = $1; }
  ;
factor
  : DOUBLE_LITERAL
  { printf("%lf\n", ($1)->value.real); }
  | LPAREN expr RPAREN
  { $$ = $2; }
  ;
%%
int yyerror(char const *str) {
  extern char *yytext;
  fprintf(stderr, "parser error near %s\n", yytext);
  return 0;
}

