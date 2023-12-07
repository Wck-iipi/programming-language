#include "./error.h"

bool Error::hadError = false;

void Error::error(int line, std::string message) { report(line, "", message); }

void Error::report(int line, std::string where, std::string message) {
  throw std::runtime_error("[line " + std::to_string(line) + "] Error" + where +
                           ": " + message);
  hadError = true;
}
