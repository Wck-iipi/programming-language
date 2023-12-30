#include "./token.h"
#include "error.h"
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>

class Environment {
  std::map<std::string,
           std::variant<int, double, std::string, bool, std::monostate>>
      values;

public:
  std::optional<std::shared_ptr<Environment>> enclosing;
  Environment() {}

  Environment(Environment &other)
      : values(other.values), enclosing(other.enclosing) {}
  void
  define(std::string name,
         std::variant<int, double, std::string, bool, std::monostate> value);
  void
  assign(Token name,
         std::variant<int, double, std::string, bool, std::monostate> value);

  std::variant<int, double, std::string, bool, std::monostate> get(Token name);
};
