#include "token.h"

std::string Token::toString() {
  return std::to_string(type) + " " + lexeme + " " + literal;
}
Token::Token(TokenType type, std::string lexeme, std::string literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}
