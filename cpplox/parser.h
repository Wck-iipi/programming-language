#pragma once
#include "./Expr.h"
#include "./Stmt.h"
#include "./error.h"
#include "./token.h"
#include <memory>
#include <string>
#include <variant>
#include <vector>

class Parser {
  class ParseError : public std::runtime_error {
  public:
    ParseError();
  };

private:
  const std::vector<Token> tokens;
  bool match(std::vector<TokenType> types);
  int current = 0;
  bool check(TokenType type);
  bool isAtEnd();

  Token advance();
  Token peek();
  Token previous();
  Token consume(TokenType type, std::string message);
  ParseError error(Token token, std::string message);
  void synchronize();

  Expr expression();
  Expr equality();
  Expr comparison();
  Expr term();
  Expr factor();
  Expr unary();
  Expr primary();
  Expr assignment();
  Expr orExpr();
  Expr andExpr();

  Stmt statement();
  Stmt printStatement();
  Stmt expressionStatement();
  Stmt declaration();
  Stmt varDeclaration();
  Stmt ifStatement();
  Stmt whileStatement();
  Stmt forStatement();

  std::vector<Stmt> block();

public:
  Parser(const std::vector<Token> tokens);
  std::vector<Stmt> parse();
};
