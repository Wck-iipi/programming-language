// Path: /Users/rakeshkainthla/development/programming-language/cpplox//Expr.h
// This file was automatically generated by generateAST.cpp
#pragma once
#include "./token.h"
#include <any>
#include <iostream>
#include <memory>
class Binary;
class Grouping;
class Literal;
class Unary;
using Expr = std::variant<std::shared_ptr<Binary>, std::shared_ptr<Grouping>,
                          std::shared_ptr<Literal>, std::shared_ptr<Unary>>;
class Binary {
public:
  Binary(Expr left, Token op, Expr right) : left(left), op(op), right(right) {}
  const Expr left;
  const Token op;
  const Expr right;
};
class Grouping {
public:
  Grouping(Expr expression) : expression(expression) {}
  const Expr expression;
};
class Literal {
public:
  Literal(std::variant<int, double, std::string, bool, std::monostate> value)
      : value(value) {}
  const std::variant<int, double, std::string, bool, std::monostate> value;
};
class Unary {
public:
  Unary(Token op, Expr right) : op(op), right(right) {}
  const Token op;
  const Expr right;
};