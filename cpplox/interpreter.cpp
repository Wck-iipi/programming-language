#include "./interpreter.h"
Environment environment;

struct Interpreter { // Visitor for Expr
  std::variant<int, double, std::string, bool, std::monostate>
  operator()(std::shared_ptr<Assign> expr) {
    std::variant<int, double, std::string, bool, std::monostate> value =
        InterpreterHelper::evaluate(expr);
    environment.assign(expr->left, value);
    return value;
  }

  std::variant<int, double, std::string, bool, std::monostate>
  operator()(std::shared_ptr<Literal> expr) {
    return expr->value;
  }

  std::variant<int, double, std::string, bool, std::monostate>
  operator()(std::shared_ptr<Grouping> expr) {
    return InterpreterHelper::evaluate(expr->expression);
  }

  std::variant<int, double, std::string, bool, std::monostate>
  operator()(std::shared_ptr<Unary> expr) {
    std::variant<int, double, std::string, bool, std::monostate> right =
        InterpreterHelper::evaluate(expr->right);

    switch (expr->op.type) {
    case MINUS:
      if (std::holds_alternative<double>(right)) {
        return -std::get<double>(right);
      } else {
        Error::report(expr->op.line, expr->op.lexeme,
                      "Minus can only be used with type Number");
      }
    case BANG:
      if (std::holds_alternative<bool>(right)) {
        return !std::get<bool>(right);
      } else if (std::holds_alternative<std::monostate>(right)) {
        return true;
      } else {
        Error::report(expr->op.line, expr->op.lexeme,
                      "Bang can only be used with type Boolean or NIL values");
      }
    default:
      Error::report(expr->op.line, expr->op.lexeme, "Wrong type with operator");
    }

    return "Not reachable";
  }
  std::variant<int, double, std::string, bool, std::monostate>
  operator()(std::shared_ptr<Binary> expr) {
    std::variant<int, double, std::string, bool, std::monostate> left =
        InterpreterHelper::evaluate(expr->left);
    std::variant<int, double, std::string, bool, std::monostate> right =
        InterpreterHelper::evaluate(expr->right);

    if (std::holds_alternative<double>(left) &&
        std::holds_alternative<double>(right)) {
      switch (expr->op.type) {
      case MINUS:
        return std::get<double>(left) - std::get<double>(right);
      case SLASH:
        return std::get<double>(left) / std::get<double>(right);
      case STAR:
        return std::get<double>(left) * std::get<double>(right);
      case PLUS:
        return std::get<double>(left) + std::get<double>(right);
      case GREATER:
        return std::get<double>(left) > std::get<double>(right);
      case GREATER_EQUAL:
        return std::get<double>(left) >= std::get<double>(right);
      case LESS:
        return std::get<double>(left) < std::get<double>(right);
      case LESS_EQUAL:
        return std::get<double>(left) <= std::get<double>(right);
      case BANG_EQUAL:
        return std::get<double>(left) != std::get<double>(right);
      case EQUAL_EQUAL:
        return std::get<double>(left) == std::get<double>(right);
      default:
        Error::report(expr->op.line, expr->op.lexeme,
                      "Wrong type with operator");
      }

    } else if (std::holds_alternative<bool>(left) &&
               std::holds_alternative<bool>(right)) {

      switch (expr->op.type) {
      case BANG_EQUAL:
        return std::get<bool>(left) != std::get<bool>(right);
      case EQUAL_EQUAL:
        return std::get<bool>(left) == std::get<bool>(right);
      default:
        Error::report(expr->op.line, expr->op.lexeme,
                      "Wrong type with operator");
      }

    } else if (std::holds_alternative<std::string>(left) &&
               std::holds_alternative<std::string>(right)) {
      switch (expr->op.type) {
      case BANG_EQUAL:
        return std::get<std::string>(left) != std::get<std::string>(right);
      case EQUAL_EQUAL:
        return std::get<std::string>(left) == std::get<std::string>(right);
      case PLUS:
        return std::get<std::string>(left) + std::get<std::string>(right);
      default:
        Error::report(expr->op.line, expr->op.lexeme,
                      "Wrong type with operator");
      }

    } else if (std::holds_alternative<std::monostate>(left)) {
      if (std::holds_alternative<std::monostate>(right)) {
        switch (expr->op.type) {
        case BANG_EQUAL:
          return false;
        case EQUAL_EQUAL:
          return true;
        default:
          Error::report(expr->op.line, expr->op.lexeme,
                        "Wrong type with operator");
        }
      } else if (std::holds_alternative<bool>(right)) {
        switch (expr->op.type) {
        case BANG_EQUAL:
          return true;
        case EQUAL_EQUAL:
          return false;
        default:
          Error::report(expr->op.line, expr->op.lexeme,
                        "Wrong type with operator");
        }
      } else {
        Error::report(expr->op.line, expr->op.lexeme,
                      "Wrong type with operator");
      }

    } else {
      Error::report(expr->op.line, expr->op.lexeme, "Wrong type with operator");
    }
    return "Unreachable code";
  }
  std::variant<int, double, std::string, bool, std::monostate>
  operator()(std::shared_ptr<Variable> expr) {
    return environment.get(expr->name);
  }
};

struct InterpreterStmt {
  void operator()(std::shared_ptr<Expression> stmt) {
    InterpreterHelper::evaluate(stmt->expression);
  }
  void operator()(std::shared_ptr<Print> stmt) {
    std::variant<int, double, std::string, bool, std::monostate> value =
        InterpreterHelper::evaluate(stmt->expression);
    std::cout << Token::literalToString(value) << std::endl;
  }
  void operator()(std::shared_ptr<Var> stmt) {
    std::variant<int, double, std::string, bool, std::monostate> value;
    if (stmt->initializer.has_value()) {
      value = InterpreterHelper::evaluate(stmt->initializer.value());
    }
    environment.define(stmt->name.lexeme, value);
  }
};

std::variant<int, double, std::string, bool, std::monostate>
InterpreterHelper::evaluate(Expr expr) {
  return std::visit(Interpreter{}, expr);
}

void InterpreterHelper::interpret(std::vector<Stmt> stmts) {
  for (Stmt stmt : stmts) {
    std::visit(InterpreterStmt{}, stmt);
  }
}
