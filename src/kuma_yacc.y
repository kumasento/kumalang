%{
#include <stdio.h>
#include <stdlib.h>

#include "kuma_ast.h"
#include "kuma_interpreter.h"

// To enable debug verbose output
#define YYDEBUG 2

// To make compiler happy
#if YYBISON
int yyerror(const char *s);
int yylex();
#endif
%}
%union {
  Expression    *expression;
  Statement     *statement;
  StatementList *statement_list;
}
%token <expression> DOUBLE_LITERAL INT_LITERAL
%token ADD SUB MUL DIV CR LPAREN RPAREN LCURLY RCURLY
%type <expression> expression term factor
%type <statement> statement
%type <statement_list> statement_list
%%
statement_list
  : statement
  { 
    $$ = create_statement_list($1, NULL); 
    print_statement_list($$); 
  }
  | statement_list CR statement
  { 
    $$ = create_statement_list($3, $1); 
    print_statement_list($$);
  }
  ;
statement
  : expression 
  { $$ = create_expression_statement($1); }
  | LCURLY statement_list RCURLY
  { $$ = create_block_statement($2); }
  ;
expression
  : expression ADD term 
  { $$ = create_binary_expression(ADD_BINARY_EXPRESSION, $1, $3); }
  | expression SUB term 
  { $$ = create_binary_expression(SUB_BINARY_EXPRESSION, $1, $3); }
  | term 
  { $$ = $1; }
  ;
term
  : term MUL factor 
  { $$ = create_binary_expression(MUL_BINARY_EXPRESSION, $1, $3); }
  | term DIV factor 
  { $$ = create_binary_expression(DIV_BINARY_EXPRESSION, $1, $3); }
  | factor
  { $$ = $1; }
  ;
factor
  : DOUBLE_LITERAL
  | INT_LITERAL
  | LPAREN expression RPAREN
  { $$ = $2; }
  ;
%%
int yyerror(char const *str) {
  extern char *yytext;
  fprintf(stderr, "parser error near %s\n", yytext);
  return 0;
}

