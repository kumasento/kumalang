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
<INITIAL>([1-9][0-9]*)|0 {
  yylval.expression = malloc(sizeof(Expression));
  yylval.expression->type = INTEGER_CONST_EXPRESSION;
  sscanf(yytext, "%d", &yylval.expression->value.integer);
  return INT_LITERAL; 
}
<INITIAL>([0-9]+\.[0-9]+) {
  yylval.expression = malloc(sizeof(Expression));
  yylval.expression->type = REAL_CONST_EXPRESSION;
  sscanf(yytext, "%lf", &yylval.expression->value.real);
  return DOUBLE_LITERAL;
}
<INITIAL>[ \t] ; /* Just ignore */
<INITIAL>. {
  fprintf(stderr, "Lexical error!\n");
  exit(1);
}
%%

