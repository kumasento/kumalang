
#include "kuma_ast.h"

Expr *create_binary_expr(ExprType type, Expr *e1, 
    Expr *e2)
{
  Expr *e = malloc(sizeof(Expr));
  e->type = type;
  e->value.binary.e1 = e1;
  e->value.binary.e2 = e2;
  return e;
}
