#include "./token.h"
#include "error.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>

class Environment {
  std::map<std::string,
           std::variant<int, double, std::string, bool, std::monostate>>
      values;

public:
  void
  define(std::string name,
         std::variant<int, double, std::string, bool, std::monostate> value);
  void
  assign(Token name,
         std::variant<int, double, std::string, bool, std::monostate> value);

  std::variant<int, double, std::string, bool, std::monostate> get(Token name);
};
