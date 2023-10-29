#include "scanner.h"
#include "token.h"
#include <iostream>
#include <vector>

Scanner::Scanner(std::string source) : source(source) {}
std::vector<Token> Scanner::scanTokens() { std::cout << source << std::endl; }
