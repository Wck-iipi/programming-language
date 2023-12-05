// Copyright
#include "scanner.h"
#include "token.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void runFile(std::string path);
void runPrompt();
void run(std::string source);

int main(int argc, char **argv) {
  if (argc > 1) {
    std::cout << "Usage: cpplox [script]" << std::endl;
    return -1;
  } else if (argc == 2) {
    runFile(argv[0]);
  } else {
    runPrompt();
  }
  return 0;
}

void runFile(std::string path) {
  std::fstream sourceFile(path, std::ios::binary);
  if (sourceFile) {
    std::ostringstream oss;
    oss << sourceFile.rdbuf();
    std::string content = oss.str();
    run(content);

  } else {
    throw std::runtime_error("Could not open file");
  }
}

void runPrompt() {
  std::string line;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, line);
    if (line.empty())
      break;
    run(line);
  }
}

void run(std::string source) {
  Scanner scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();
  for (Token token : tokens) {
    std::cout << token.toString() << std::endl;
  }
}
