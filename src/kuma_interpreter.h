#ifndef KUMA_INTERPRETER_H__
#define KUMA_INTERPRETER_H__

#include "kuma_ast.h"

typedef struct Interpreter_tag {
  StatementList *statement_list;
} Interpreter;

Interpreter* get_global_interpreter();

#endif
