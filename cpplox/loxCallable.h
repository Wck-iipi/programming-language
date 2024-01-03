#pragma once

#include "interpreter.h"
#include "token.h"
#include <vector>
class LoxCallable {
public:
  int arity();
  loxTypes call(Interpreter interpreter, std::vector<loxTypes> arguments);
};
