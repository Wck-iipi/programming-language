#pragma once
#include "token.h"
#include <iostream>
#include <string>
#include <vector>

class Scanner {
private:
  std::string source;
  int start;
  int current;
  int line;
  std::vector<Token> tokens;
  bool isAtEnd(std::string source);
  void scanToken();
  void addToken(TokenType type, std::string literal);
  bool match(char expected);
  void string();

public:
  Scanner(std::string source);
  std::vector<Token> scanTokens();
};
