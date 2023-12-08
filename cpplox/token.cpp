#include "./token.h"

std::vector<std::string> tokenType = {
    "LEFT_PAREN", "RIGHT_PAREN",   "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
    "DOT",        "MINUS",         "PLUS",       "SEMICOLON",   "SLASH",
    "STAR",       "BANG",          "BANG_EQUAL", "EQUAL",       "EQUAL_EQUAL",
    "GREATER",    "GREATER_EQUAL", "LESS",       "LESS_EQUAL",  "IDENTIFIER",
    "STRING",     "NUMBER",        "AND",        "CLASS",       "ELSE",
    "FALSE",      "FUN",           "FOR",        "IF",          "NIL",
    "OR",         "PRINT",         "RETURN",     "SUPER",       "THIS",
    "TRUE",       "VAR",           "WHILE",      "EOF_TOKEN"};

std::string Token::toString() {
  return tokenType[this->type] + "," + this->lexeme + "," +
         std::any_cast<std::string>(this->literal) + "," +
         std::to_string(this->line);
}
Token::Token(TokenType type, std::string lexeme, std::any literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}
