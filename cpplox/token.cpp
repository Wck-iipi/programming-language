#include "token.h"
#include "scanner.h"
#include <iostream>
#include <vector>

std::string Token::toString(TokenType type, std::string lexeme,
                            std::string literal, int line) {
  return std::to_string(type) + " " + lexeme + " " + literal;
};
Token::Token(TokenType type, std::string lexeme, std::string literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}
