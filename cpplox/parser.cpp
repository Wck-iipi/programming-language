#include "./parser.h"
#include "./error.h"

Parser::Parser(const std::vector<Token> tokens) : tokens(tokens) {}

Expr Parser::expression() { return this->equality(); }

Expr Parser::equality() {
  Expr expr = this->comparison();

  while (match({BANG_EQUAL, EQUAL})) {
    Token op = this->previous();
    Expr right = this->comparison();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

bool Parser::match(std::vector<TokenType> types) {
  for (const auto &type : types) {
    if (this->check(type)) {
      this->advance();
      return true;
    }
  }

  return false;
}

bool Parser::isAtEnd() { return this->peek().type == EOF_TOKEN; }

Token Parser::peek() { return this->tokens.at(current); }

Token Parser::previous() { return this->tokens.at(current - 1); }

bool Parser::check(TokenType type) {
  if (isAtEnd()) {
    return false;
  }
  return this->peek().type == type;
}

Expr Parser::comparison() {
  Expr expr = this->term();
  while (this->match({GREATER, GREATER_EQUAL, LESS_EQUAL, LESS})) {
    Token op = this->previous();
    Expr right = this->term();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

Token Parser::advance() {
  if (!isAtEnd()) {
    ++this->current;
  }
  return this->previous();
}

Expr Parser::term() {
  Expr expr = factor();
  while (this->match({MINUS, PLUS})) {
    Token op = this->previous();
    Expr right = this->factor();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

Expr Parser::factor() {
  Expr expr = this->unary();
  while (this->match({SLASH, STAR})) {
    Token op = this->previous();
    Expr right = this->unary();
    expr = std::make_shared<Binary>(expr, op, right);
  }
  return expr;
}

Expr Parser::unary() {
  while (this->match({BANG, MINUS})) {
    Token op = this->previous();
    Expr right = this->unary();
    return std::make_shared<Unary>(op, right);
  }
  return primary();
}

Expr Parser::primary() {
  if (this->match({FALSE}))
    return std::make_shared<Literal>(false);
  if (this->match({TRUE}))
    return std::make_shared<Literal>(true);
  if (this->match({NIL}))
    return std::make_shared<Literal>(std::monostate{});
  if (this->match({NUMBER, STRING})) {
    return std::make_shared<Literal>(
        previous().literal); // change this as this is std::any of std::variant
  }
  if (this->match({LEFT_PAREN})) {
    Expr expr = expression();
    consume(RIGHT_PAREN, "Expect ')' after expression.");
    return std::make_shared<Grouping>(expr);
  }
  throw this->error(peek(), "Expected expression.");
}

Token Parser::consume(TokenType type, std::string message) {
  if (this->check(type))
    return this->advance();
  throw this->error(peek(), message);
}

Parser::ParseError::ParseError() : std::runtime_error("Parse Error") {
  std::cout << "Parse Error" << std::endl;
}

Parser::ParseError Parser::error(Token token, std::string message) {
  Error::error(token, message);
  Parser::ParseError parseError;
  return parseError;
}

void Parser::synchronize() {
  this->advance();

  while (!isAtEnd()) {
    if (previous().type == SEMICOLON)
      return;

    switch (peek().type) {
    case CLASS:
    case FUN:
    case VAR:
    case FOR:
    case IF:
    case WHILE:
    case PRINT:
    case RETURN:
      return;
    default:
      break;
    }

    this->advance();
  }
}

Expr Parser::parse() {
  try {
    return this->expression();
  } catch (ParseError error) {
    return std::make_shared<Literal>(std::monostate{});
  }
}
