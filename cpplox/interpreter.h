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

void executeBlock(std::vector<Stmt> statements,
                  std::shared_ptr<Environment> newEnvironment);

struct Interpreter; // Visitor for Expr
struct InterpreterStmt;

namespace InterpreterHelper {
struct loxTypesToBool;
loxTypes evaluate(Expr expr);
void interpret(std::vector<Stmt> stmts);
}; // namespace InterpreterHelper
namespace InterpreterStmtHelper {};
