#pragma once
#include "../ExprCpp.h"
#include <any>
#include <memory>
#include <string>
#include <vector>

struct ASTPrinterExpr;
std::string toString(std::any val);
std::string parenthesize(std::string name, std::vector<Expr> exprs);
std::string print(Expr expr);
void call_print();
