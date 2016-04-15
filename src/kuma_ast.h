#ifndef KUMA_AST_H__
#define KUMA_AST_H__

#include <stdlib.h>

/* Expression */
typedef enum {
  /* constants */
  INTEGER_CONST_EXPRESSION = 0,
  REAL_CONST_EXPRESSION,
  /* binary expressions */
  ADD_BINARY_EXPRESSION,
  SUB_BINARY_EXPRESSION,
  MUL_BINARY_EXPRESSION,
  DIV_BINARY_EXPRESSION
} ExpressionType;

typedef struct Expression_tag Expression;

/* binary expression content */
typedef struct { Expression *e1, *e2; } BinaryExpression;

struct Expression_tag {
  ExpressionType type;
  union {
    double            real;
    int               integer;
    Expression        *expression;
    BinaryExpression  binary_expression;
  } value;
};

/* Statement */
typedef struct Statement_tag Statement;

typedef struct StatementList_tag {
  Statement *statement;
  struct StatementList_tag *next;
} StatementList;

typedef enum {
  EXPRESSION_STATEMENT = 0,
  BLOCK_STATEMENT
} StatementType;

typedef struct Block_tag {
  StatementList *statement_list;
} Block;

struct Statement_tag {
  StatementType type;
  int line_num;
  union {
    Expression  *expression;
    Block       block;
  } content;
};

/* create */
Expression *create_binary_expression(ExpressionType type, Expression *e1, Expression *e2);
Statement *create_expression_statement(Expression* expression);
Statement *create_block_statement(StatementList *statement_list);
StatementList *create_statement_list(Statement *statement, StatementList *next);

/* utilities */
void print_expression(Expression *expression);
void print_statement_list(StatementList *statement_list);
void print_statement(Statement *statement);

#endif
