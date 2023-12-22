#pragma once
#include "../Expr.h"
#include <any>
#include <memory>
#include <string>
#include <vector>

struct ASTPrinterExpr;
namespace ASTPrinterHelper {
std::string parenthesize(std::string name, std::vector<Expr> exprs);
std::string print(Expr expr);
void call_print();
} // namespace ASTPrinterHelper
