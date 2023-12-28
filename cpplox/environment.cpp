#include "./environment.h"

void Environment::define(
    std::string name,
    std::variant<int, double, std::string, bool, std::monostate> value) {
  this->values.insert({name, value});
}
std::variant<int, double, std::string, bool, std::monostate>
Environment::get(Token name) {
  if (this->values.count(name.lexeme) > 0) {
    return this->values.at(name.lexeme);
  }
  throw new std::runtime_error("Undefined variable '" + name.lexeme + "'.");
}

void Environment::assign(
    Token name,
    std::variant<int, double, std::string, bool, std::monostate> value) {
  this->values[name.lexeme] = value;
  return;
  Error::report(name.line, name.lexeme,
                "Undefined variable '" + name.lexeme + "'");
}
