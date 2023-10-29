#pragma once
#include "token.h"
#include <iostream>
#include <string>
#include <vector>

class Scanner {
private:
  std::string source;

public:
  Scanner(std::string source);
  std::vector<Token> scanTokens();
};
