#ifndef KUMA_AST_H__
#define KUMA_AST_H__

#include <stdlib.h>

typedef enum {
  /* constants */
  DOUBLE_LITERAL_EXPR,
  /* binary expressions */
  ADD_BINARY_EXPR,
  SUB_BINARY_EXPR,
  MUL_BINARY_EXPR,
  DIV_BINARY_EXPR
} ExprType;

typedef struct Expr_tag Expr;

/* binary expression content */
typedef struct { Expr *e1, *e2; } BinaryExpr;

struct Expr_tag {
  ExprType type;
  union {
    double      real;
    int         integer;
    Expr        *expr;
    BinaryExpr  binary;
  } value;
};

Expr *create_binary_expr(ExprType type, Expr *e1, Expr *e2);

#endif
