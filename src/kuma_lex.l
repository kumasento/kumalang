%{
#include <stdio.h>
#include "../y.tab.h" // include auto-generated yacc header

// To make llibrary liking happy
int yywrap() {
  return 1; 
}
%}
%%
"+"   return ADD;
"-"   return SUB;
"*"   return MUL;
"/"   return DIV;
"\n"  return CR;
([1-9][0-9]*)|0|([0-9]+\.[0-9]+) {
  /* General lexer for number */
  double temp;
  sscanf(yytext, "%lf", &temp);
  /* Set data */
  yylval.double_value = temp;
  /* Set token id */
  return DOUBLE_LITERAL;
}
[ \t] ; /* Just ignore */
. {
  fprintf(stderr, "Lexical error!\n");
  exit(1);
}
%%

