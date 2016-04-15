#ifndef KUMA_AST_H__
#define KUMA_AST_H__

#include <stdlib.h>

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

/* create */
Expression *create_binary_expr(ExpressionType type, Expression *e1, Expression *e2);

/* utilities */
void print_binary_expression(Expression *expression);
void print_expression(Expression *expression);

#endif
