#pragma once
#include "./Expr.h"
#include "./token.h"
#include <string>
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
  Expr expression();
  Expr equality();
  Expr comparison();
  Expr term();
  Expr factor();
  Expr unary();
  Expr primary();
  Token consume(TokenType type, std::string message);
  ParseError error(Token token, std::string message);
  void synchronize();

public:
  Parser(const std::vector<Token> tokens);
  Expr parse();
};
