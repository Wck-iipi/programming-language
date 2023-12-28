#pragma once
#include "./Expr.h"
#include "./Stmt.h"
#include "./environment.h"
#include "./error.h"
#include <any>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct Interpreter; // Visitor for Expr
struct InterpreterStmt;

namespace InterpreterHelper {
std::variant<int, double, std::string, bool, std::monostate>
evaluate(Expr expr);
void interpret(std::vector<Stmt> stmts);
}; // namespace InterpreterHelper
namespace InterpreterStmtHelper {};
