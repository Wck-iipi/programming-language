#include "./error.h"

bool Error::hadError = false;

void Error::error(int line, std::string message) { report(line, "", message); }
void Error::error(Token token, std::string message) {
  if (token.type == EOF_TOKEN) {
    report(token.line, " at end", message);
  } else {
    report(token.line, " at '" + token.lexeme + "'", message);
  }
}

void Error::report(int line, std::string where, std::string message) {
  throw std::runtime_error("[line " + std::to_string(line + 1) + "] Error" +
                           where + ": " + message);
  hadError = true;
}
