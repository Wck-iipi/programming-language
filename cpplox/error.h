#pragma once
#include <iostream>
#include <string>

namespace Error {
extern bool hadError;
void error(int line, std::string message);
void report(int line, std::string where, std::string message);
} // namespace Error
