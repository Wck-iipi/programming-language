#include "./scanner.h"
#include "./error.h"
#include "./token.h"
#include <variant>

std::map<std::string, TokenType> Scanner::keywords = {
    {"and", AND},   {"class", CLASS}, {"else", ELSE},     {"false", FALSE},
    {"for", FOR},   {"fun", FUN},     {"if", IF},         {"nil", NIL},
    {"or", OR},     {"print", PRINT}, {"return", RETURN}, {"super", SUPER},
    {"this", THIS}, {"true", TRUE},   {"var", VAR},       {"while", WHILE}};
Scanner::Scanner(std::string source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd(source)) {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(EOF_TOKEN, "", std::monostate{}, line));
  return tokens;
}

bool Scanner::isAtEnd(std::string source) { return current >= source.length(); }

void Scanner::scanToken() {
  char c = source.at(current++);
  switch (c) {
  case '(':
    addToken(LEFT_PAREN, std::monostate{});
    break;
  case ')':
    addToken(RIGHT_PAREN, std::monostate{});
    break;
  case '{':
    addToken(LEFT_BRACE, std::monostate{});
    break;
  case '}':
    addToken(RIGHT_BRACE, std::monostate{});
    break;
  case ',':
    addToken(COMMA, std::monostate{});
    break;
  case '.':
    addToken(DOT, std::monostate{});
    break;
  case '-':
    addToken(match('-') ? DECREMENT : MINUS, std::monostate{});
    break;
  case '+':
    addToken(match('+') ? INCREMENT : PLUS, std::monostate{});
    break;
  case ';':
    addToken(SEMICOLON, std::monostate{});
    break;
  case '*':
    addToken(STAR, std::monostate{});
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG, std::monostate{});
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER, std::monostate{});
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS, std::monostate{});
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL, std::monostate{});
    break;
  case '/':
    if (match('/')) {
      while (source.at(current) != '\n' && !isAtEnd(source))
        current++;
    } else {
      addToken(SLASH, std::monostate{});
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
    } else if (isalpha(c) || c == '_') {
      identifier();
    } else {
      Error::error(line, "Unexpected character.");
    }
  }
}

void Scanner::identifier() {
  while ((isalnum(source.at(current)) || source.at(current) == '_') &&
         !isAtEnd(source)) {
    current++;
  }
  std::string text = source.substr(start, current - start);
  if (keywords.find(text) != keywords.end()) {
    addToken(keywords[text], std::monostate{});
    return;
  }
  addToken(IDENTIFIER, std::monostate{});
}

char Scanner::peekNext() {
  if (current + 1 >= source.length())
    return '\0';
  return source.at(current + 1);
}
void Scanner::number() {
  while (!isAtEnd(source) && isdigit(source.at(current))) {
    current++;
  }
  if (!isAtEnd(source) && source.at(current) == '.' && isdigit(peekNext())) {
    current++;
    while (!isAtEnd(source) && isdigit(source.at(current))) {
      current++;
    }
  }
  addToken(NUMBER, stod(source.substr(start, current - start)));
}

bool Scanner::match(char expected) {
  if (isAtEnd(source))
    return false;
  if (source.at(current) != expected)
    return false;
  current++;
  return true;
}

void Scanner::addToken(
    TokenType type, std::variant<double, std::string, std::monostate> literal) {
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
