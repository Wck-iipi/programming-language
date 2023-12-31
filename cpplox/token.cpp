#include "./token.h"

std::vector<std::string> tokenType = {
    "LEFT_PAREN", "RIGHT_PAREN",   "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
    "DOT",        "MINUS",         "PLUS",       "SEMICOLON",   "SLASH",
    "STAR",       "BANG",          "BANG_EQUAL", "EQUAL",       "EQUAL_EQUAL",
    "GREATER",    "GREATER_EQUAL", "LESS",       "LESS_EQUAL",  "INCREMENT",
    "DECREMENT",  "IDENTIFIER",    "STRING",     "NUMBER",      "AND",
    "CLASS",      "ELSE",          "FALSE",      "FUN",         "FOR",
    "IF",         "NIL",           "OR",         "PRINT",       "RETURN",
    "SUPER",      "THIS",          "TRUE",       "VAR",         "WHILE",
    "EOF_TOKEN"};

struct VariantToString {
  std::string operator()(double value) const { return std::to_string(value); }

  std::string operator()(const std::string &value) const { return value; }

  std::string operator()(std::monostate) const { return "NULL"; }

  std::string operator()(int value) const { return std::to_string(value); }

  std::string operator()(bool value) const { return value ? "true" : "false"; }
};

std::string Token::literalToString(loxTypes value) {
  return std::visit(VariantToString{}, value);
}

std::string Token::toString() {
  return tokenType[this->type] + "," + this->lexeme + "," +
         Token::literalToString(this->literal) + "," +
         std::to_string(this->line);
}
Token::Token(TokenType type, std::string lexeme, loxTypes literal, int line)
    : line(line), type(type), literal(literal), lexeme(lexeme) {}
