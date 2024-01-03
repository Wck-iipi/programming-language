#include "./environment.h"

void Environment::define(std::string name, loxTypes value) {
  try {
    if (this->values.count(name) > 0) {
      // TODO: throw error when same variable in same scope is redefined
      // throw std::runtime_error("Variable is already defined " + name);
      this->values[name] = value;
      return;
    }
    this->values.insert({name, value});
  } catch (const std::runtime_error &e) {
    std::cerr << "Caught expection: " << e.what() << std::endl;
  }
}

loxTypes Environment::get(Token name) {
  try {
    if (this->values.count(name.lexeme) > 0) {
      return this->values.at(name.lexeme);
    }
    if (enclosing.has_value()) {
      return enclosing.value()->get(name);
    }

    throw std::runtime_error("Undefined variable '" + name.lexeme + "'.");
  } catch (std::runtime_error &e) {
    std::cerr << "Caught expection: " << e.what() << std::endl;
  }
}

void Environment::assign(Token name, loxTypes value) {
  if (this->values.count(name.lexeme) > 0) {
    this->values[name.lexeme] = value;
    return;
  }
  if (enclosing.has_value()) {
    enclosing.value()->assign(name, value);
    return;
  }
  Error::report(name.line, name.lexeme,
                "Undefined variable '" + name.lexeme + "'");
}
