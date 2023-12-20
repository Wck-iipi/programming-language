#include "./ASTPrinter.h"

std::string toString(std::any expr) {
  std::string result;
  if (expr.type() == typeid(int)) {
    result = std::to_string(std::any_cast<int>(expr));
  } else if (expr.type() == typeid(double)) {
    result = std::to_string(std::any_cast<double>(expr));
  } else if (expr.type() == typeid(std::string)) {
    result = std::any_cast<std::string>(expr);
  } else {
    result = "Unsupported type";
  }
  return result;
}
std::string parenthesize(std::string name, std::vector<Expr> exprs);

struct ASTPrinterExpr {
  std::string operator()(std::shared_ptr<Binary> expr) {
    return parenthesize(expr->op.lexeme, {expr->left, expr->right});
  }

  std::string operator()(std::shared_ptr<Grouping> expr) {
    return parenthesize("group", {expr->expression});
  }
  //
  std::string operator()(std::shared_ptr<Literal> expr) {
    if (!expr->value.has_value())
      return "nil";
    return toString(expr->value);
  }

  std::string operator()(std::shared_ptr<Unary> expr) {
    return parenthesize(expr->op.lexeme, {expr->right});
  }
};

std::string parenthesize(std::string name, std::vector<Expr> exprs) {
  std::string result = "(" + name;
  for (auto &expr : exprs) {
    result += " ";
    result += std::visit(ASTPrinterExpr{}, expr);
  }
  result += ")";

  return result;
}
std::string print(Expr expr) { return std::visit(ASTPrinterExpr{}, expr); }

void call_print() {
  Expr a =
      std::make_shared<Unary>(Token(TokenType::MINUS, "-", std::monostate{}, 1),
                              std::make_shared<Literal>(std::any(123)));
  Expr b =
      std::make_shared<Grouping>(std::make_shared<Literal>(std::any(45.67)));
  Expr expression = std::make_shared<Binary>(
      a, Token(TokenType::STAR, "*", std::monostate{}, 1), b);

  std::cout << print(expression);
}
