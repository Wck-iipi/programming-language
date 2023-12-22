#pragma once
#include "token.h"
#include <iostream>
#include <string>

namespace Error {
extern bool hadError;
void error(int line, std::string message);
void error(Token token, std::string message);
void report(int line, std::string where, std::string message);
} // namespace Error
