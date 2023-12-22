#include "./ASTPrinter.h"

struct ASTPrinterExpr { // Visitor
  std::string operator()(std::shared_ptr<Binary> expr) {
    return ASTPrinterHelper::parenthesize(expr->op.lexeme,
                                          {expr->left, expr->right});
  }

  std::string operator()(std::shared_ptr<Grouping> expr) {
    return ASTPrinterHelper::parenthesize("group", {expr->expression});
  }
  //
  std::string operator()(std::shared_ptr<Literal> expr) {
    if (std::holds_alternative<std::monostate>(expr->value))
      return "nil";
    return Token::literalToString(expr->value);
  }

  std::string operator()(std::shared_ptr<Unary> expr) {
    return ASTPrinterHelper::parenthesize(expr->op.lexeme, {expr->right});
  }
};

std::string ASTPrinterHelper::parenthesize(std::string name,
                                           std::vector<Expr> exprs) {
  std::string result = "(" + name;
  for (auto &expr : exprs) {
    result += " ";
    result += std::visit(ASTPrinterExpr{}, expr);
  }
  result += ")";

  return result;
}
std::string ASTPrinterHelper::print(Expr expr) {
  return std::visit(ASTPrinterExpr{}, expr);
}

void ASTPrinterHelper::call_print() {
  Expr a =
      std::make_shared<Unary>(Token(TokenType::MINUS, "-", std::monostate{}, 1),
                              std::make_shared<Literal>(123));
  Expr b = std::make_shared<Grouping>(std::make_shared<Literal>(45.67));
  Expr expression = std::make_shared<Binary>(
      a, Token(TokenType::STAR, "*", std::monostate{}, 1), b);

  std::cout << ASTPrinterHelper::print(expression);
}
