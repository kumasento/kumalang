
#include "kuma_interpreter.h"

static Interpreter *global_interpreter = NULL;

Interpreter *get_global_interpreter() { 
  // just like a singleton
  if (global_interpreter == NULL)
    global_interpreter = malloc(sizeof(Interpreter));
  return global_interpreter; 
}
