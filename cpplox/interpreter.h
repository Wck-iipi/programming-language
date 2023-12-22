#pragma once
#include "./Expr.h"
#include <any>
#include <memory>
#include <string>
#include <vector>

struct Interpreter; // Visitor

namespace InterpreterHelper {
static std::variant<int, double, std::string, bool, std::monostate>
evaluate(Expr expr);
void interpret(Expr expr);
}; // namespace InterpreterHelper
