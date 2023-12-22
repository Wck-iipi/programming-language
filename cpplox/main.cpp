// Copyright
#include "./Expr.h"
#include "./error.h"
#include "./interpreter.h"
#include "./parser.h"
#include "./scanner.h"
#include "./token.h"
#include "./tools/ASTPrinter.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

void runFile(std::string path);
void runPrompt();
void run(std::string source);

int main(int argc, char **argv) {
  // ASTPrinterHelper::call_print(); // print the AST

  if (argc == 1) {
    runPrompt();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    std::cout << "Usage: cpplox [script]" << std::endl;
    return -1;
  }
  return 0;
}

void runFile(std::string path) {
  std::cout << "Running file: " << path << std::endl;
  std::fstream sourceFile(path);
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
    std::cout << std::endl;
  }
}

void run(std::string source) {
  Scanner scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();
  Parser parser(tokens);
  Expr expression = parser.parse();
  InterpreterHelper::interpret(expression);

  if (Error::hadError)
    return;

  // std::cout << ASTPrinterHelper::print(expression);

  // for (Token token : tokens) {
  //   std::cout << token.toString() << std::endl;
  // }
}
