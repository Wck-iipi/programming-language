#pragma once
#include <iostream>
#include <string>
#include <variant>
#include <vector>

enum TokenType {
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  INCREMENT,
  DECREMENT,
  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,
  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  EOF_TOKEN
};
class Token {
public:
  int line;
  TokenType type;
  std::variant<int, double, std::string, bool, std::monostate> literal;
  std::string toString();
  std::string lexeme;
  Token(TokenType type, std::string lexeme,
        std::variant<int, double, std::string, bool, std::monostate> literal,
        int line);
  static std::string literalToString(
      std::variant<int, double, std::string, bool, std::monostate> value);
};
