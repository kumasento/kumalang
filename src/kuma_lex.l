%{
#include <stdio.h>
#include "kuma_ast.h"
#include "../y.tab.h" // include auto-generated yacc header

// To make llibrary liking happy
int yywrap() {
  return 1; 
}
%}
%%
<INITIAL>"+"   return ADD;
<INITIAL>"-"   return SUB;
<INITIAL>"*"   return MUL;
<INITIAL>"/"   return DIV;
<INITIAL>"\n"  return CR;
<INITIAL>"("   return LPAREN;
<INITIAL>")"   return RPAREN;
<INITIAL>([1-9][0-9]*)|0|([0-9]+\.[0-9]+) {
  yylval.expr = malloc(sizeof(Expr));
  yylval.expr->type = DOUBLE_LITERAL_EXPR;
  sscanf(yytext, "%lf", &yylval.expr->value.real);
  return DOUBLE_LITERAL;
}
<INITIAL>[ \t] ; /* Just ignore */
<INITIAL>. {
  fprintf(stderr, "Lexical error!\n");
  exit(1);
}
%%

