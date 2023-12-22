// Path: /Users/rakeshkainthla/development/programming-language/cpplox//Stmt.h
// This file was automatically generated by generateAST.cpp
#pragma once
#include "./Expr.h"
#include "./token.h"
#include <any>
#include <iostream>
#include <memory>
class Expression;
class Print;
using Stmt = std::variant<std::shared_ptr<Expression>, std::shared_ptr<Print>>;
class Expression {
public:
  Expression(Expr expression) : expression(expression) {}
  const Expr expression;
};
class Print {
public:
  Print(Expr expression) : expression(expression) {}
  const Expr expression;
};