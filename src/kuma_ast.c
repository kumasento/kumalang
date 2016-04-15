
#include <stdio.h>
#include <stdlib.h>
#include "kuma_ast.h"

/* create */
Expression *create_binary_expr(ExpressionType type, Expression *e1, 
    Expression *e2)
{
  Expression *e = malloc(sizeof(Expression));
  e->type = type;
  e->value.binary_expression.e1 = e1;
  e->value.binary_expression.e2 = e2;
  return e;
}

/* utilities */

// global variables 
int print_level = 0;

void print_tabs() {
  int i; 
  for (i = 0; i < print_level; i ++) printf("\t");
  return ;
}

// print colorful type name
void print_binary_expression_type_name(const char *type_name) { 
  printf("\x1b[33m[%s]:\x1b[0m", type_name); 
}

void print_const_expression_type_name(const char *type_name) { 
  printf("\x1b[32m[%s]:\x1b[0m", type_name); 
}

void print_binary_expression(Expression *expression) {
  print_tabs();
  switch (expression->type) {
    case ADD_BINARY_EXPRESSION: 
      print_binary_expression_type_name("ADD_BINARY_EXPRESSION"); break;
    case SUB_BINARY_EXPRESSION: 
      print_binary_expression_type_name("SUB_BINARY_EXPRESSION"); break;
    case MUL_BINARY_EXPRESSION: 
      print_binary_expression_type_name("MUL_BINARY_EXPRESSION"); break;
    case DIV_BINARY_EXPRESSION: 
      print_binary_expression_type_name("DIV_BINARY_EXPRESSION"); break;
    default:
      fprintf(stderr, "Error binary expression type: %d\n", expression->type);
      exit(1);
  }
  printf("\n"); 

  print_level ++;
  print_expression(expression->value.binary_expression.e1);
  print_expression(expression->value.binary_expression.e2);
  print_level --;

  return ;
}

void print_const_expression(Expression *expression) {
  print_tabs();
  switch(expression->type) {
    case INTEGER_CONST_EXPRESSION:
      print_const_expression_type_name("INTEGER");
      break;
    case REAL_CONST_EXPRESSION:
      print_const_expression_type_name("REAL");
      break;
    default:
      fprintf(stderr, "Error const expression type: %d\n", expression->type);
      exit(1);
  }
  printf("\t%d\n", expression->value.integer);
}

void print_expression(Expression *expression) {
  switch (expression->type) {
    case INTEGER_CONST_EXPRESSION:
    case REAL_CONST_EXPRESSION:
      print_const_expression(expression);
      break;
    case ADD_BINARY_EXPRESSION:
    case SUB_BINARY_EXPRESSION:
    case MUL_BINARY_EXPRESSION:
    case DIV_BINARY_EXPRESSION:
      print_binary_expression(expression);
      break;
    default:
      fprintf(stderr, "Error expression type: %d\n", expression->type);
      exit(1);
  }
  return ;
}
