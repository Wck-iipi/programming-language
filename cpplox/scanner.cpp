#include "scanner.h"
#include "error.h"
#include "token.h"

Scanner::Scanner(std::string source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd(source)) {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(EOF_TOKEN, "", nullptr, line));
  return tokens;
}

bool Scanner::isAtEnd(std::string source) { return current >= source.length(); }

void Scanner::scanToken() {
  char c = source.at(current++);
  switch (c) {
  case '(':
    addToken(LEFT_PAREN, nullptr);
    break;
  case ')':
    addToken(RIGHT_PAREN, nullptr);
    break;
  case '{':
    addToken(LEFT_BRACE, nullptr);
    break;
  case '}':
    addToken(RIGHT_BRACE, nullptr);
    break;
  case ',':
    addToken(COMMA, nullptr);
    break;
  case '.':
    addToken(DOT, nullptr);
    break;
  case '-':
    addToken(MINUS, nullptr);
    break;
  case '+':
    addToken(PLUS, nullptr);
    break;
  case ';':
    addToken(SEMICOLON, nullptr);
    break;
  case '*':
    addToken(STAR, nullptr);
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG, nullptr);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER, nullptr);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS, nullptr);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL, nullptr);
    break;
  case '/':
    if (match('/')) {
      while (source.at(current) != '\n' && !isAtEnd(source))
        current++;
    } else {
      addToken(SLASH, nullptr);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  case '"':
    string();
    break;

  default:
    std::cout << "Unexpected character." << std::endl;
    break;
  }
}

bool Scanner::match(char expected) {
  if (isAtEnd(source))
    return false;
  if (source.at(current) != expected)
    return false;
  current++;
  return true;
}

void Scanner::addToken(TokenType type, std::string literal) {
  std::string text = source.substr(start, current);
  tokens.push_back(Token(type, text, literal, line));
}

void Scanner::string() {
  while (source.at(current) != '\0' && source.at(current) != '"' &&
         !isAtEnd(source)) {
    if (source.at(current) == '\n') {
      line++;
    }
    current++;
  }
  if (isAtEnd(source)) {
    Error::error(line, "Unterminated string.");
    return;
  }
  current++;                                               // goes to ending "
  addToken(STRING, source.substr(start + 1, current - 1)); // skipping the "
}
