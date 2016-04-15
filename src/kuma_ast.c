
#include <stdio.h>
#include <stdlib.h>
#include "kuma_ast.h"

/* create */
/* create expressions */
Expression *create_binary_expression(ExpressionType type, Expression *e1, 
    Expression *e2)
{
  Expression *e = malloc(sizeof(Expression));
  e->type = type;
  e->value.binary_expression.e1 = e1;
  e->value.binary_expression.e2 = e2;
  return e;
}

/* create statements */
Statement *create_expression_statement(Expression* expression) {
  Statement *statement = malloc(sizeof(Statement));
  statement->type = EXPRESSION_STATEMENT;
  statement->content.expression = expression;
  return statement;
}

Statement *create_block_statement(StatementList *statement_list) {
  Statement *statement = malloc(sizeof(Statement));
  statement->type = BLOCK_STATEMENT;
  statement->content.block.statement_list = statement_list;
  return statement;
}

StatementList *create_statement_list(Statement *statement, StatementList *next) {
  StatementList *statement_list = malloc(sizeof(StatementList));
  statement_list->statement = statement;
  statement_list->next = next;
  return statement_list;
}
/* utilities */

// global variables 
int global_print_level = 0;

void increase_print_level() { global_print_level ++; }
void decrease_print_level() { global_print_level --; }

void print_tabs() {
  int i; 
  for (i = 0; i < global_print_level; i ++) printf("  ");
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

  global_print_level ++;
  print_expression(expression->value.binary_expression.e1);
  print_expression(expression->value.binary_expression.e2);
  global_print_level --;

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

void print_statement_list(StatementList *statement_list) {
  StatementList *temp = statement_list;
  while (temp != NULL) {
    print_statement(temp->statement);
    temp = temp->next;
  }
}

void print_statement_type_name(const char *type_name) {
  printf("\x1b[34m<%s>\x1b[0m", type_name);
}

void print_statement(Statement *statement) {
  print_tabs();
  increase_print_level(); 
  switch (statement->type) {
    case EXPRESSION_STATEMENT:
      print_statement_type_name("EXPRESSION");
      printf("\n");
      print_expression(statement->content.expression);
      break;
    case BLOCK_STATEMENT:
      print_statement_type_name("BLOCK");
      printf("\n");
      print_statement_list(statement->content.block.statement_list);
      break;
    default:
      fprintf(stderr, "Error statement type: %d\n", statement->type);
      exit(1);
  }
  decrease_print_level();
}
