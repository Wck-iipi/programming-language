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
  explicit Grouping(Expr expression) : expression(expression) {}
  const Expr expression;
};

class Unary {
public:
  Unary(Token op, Expr right) : op(op), right(right) {}
  const Token op;
  const Expr right;
};

class Literal {
public:
  explicit Literal(std::any value) : value(value) {}
  const std::any value;
};
