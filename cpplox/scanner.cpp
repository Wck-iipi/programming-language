#include "./scanner.h"
#include "./error.h"
#include "./token.h"
#include <any>

Scanner::Scanner(std::string source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd(source)) {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(EOF_TOKEN, "", "", line));
  return tokens;
}

bool Scanner::isAtEnd(std::string source) { return current >= source.length(); }

void Scanner::scanToken() {
  char c = source.at(current++);
  switch (c) {
  case '(':
    addToken(LEFT_PAREN, "");
    break;
  case ')':
    addToken(RIGHT_PAREN, "");
    break;
  case '{':
    addToken(LEFT_BRACE, "");
    break;
  case '}':
    addToken(RIGHT_BRACE, "");
    break;
  case ',':
    addToken(COMMA, "");
    break;
  case '.':
    addToken(DOT, "");
    break;
  case '-':
    addToken(MINUS, "");
    break;
  case '+':
    addToken(PLUS, "");
    break;
  case ';':
    addToken(SEMICOLON, "");
    break;
  case '*':
    addToken(STAR, "");
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG, "");
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER, "");
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS, "");
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL, "");
    break;
  case '/':
    if (match('/')) {
      while (source.at(current) != '\n' && !isAtEnd(source))
        current++;
    } else {
      addToken(SLASH, "");
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
    if (isdigit(c)) {
      number();
    } else {
      Error::error(line, "Unexpected character.");
    }
  }
}

void Scanner::number() {
  while (isdigit(source.at(current))) {
    current++;
  }
  if (source.at(current) == '.' && isdigit(source.at(current + 1))) {
    current++;
    while (isdigit(source.at(current))) {
      current++;
    }
  }
  addToken(NUMBER, source.substr(start, current - start));
}

bool Scanner::match(char expected) {
  if (isAtEnd(source))
    return false;
  if (source.at(current) != expected)
    return false;
  current++;
  return true;
}

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text = source.substr(start, current - start);
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
  current++; // goes to ending "
  addToken(STRING,
           source.substr(start + 1, current - start - 2)); // skipping the "
}
