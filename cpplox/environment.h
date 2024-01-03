#include "./token.h"
#include "error.h"
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>

class Environment {
  std::map<std::string, loxTypes> values;

public:
  std::optional<std::shared_ptr<Environment>> enclosing;

  void setEquals(std::shared_ptr<Environment> env) {
    values = env->values;
    enclosing = env->enclosing;
  }

  Environment() {}

  Environment(std::shared_ptr<Environment> other) : enclosing(other) {}

  void define(std::string name, loxTypes value);
  void assign(Token name, loxTypes value);

  loxTypes get(Token name);
};
