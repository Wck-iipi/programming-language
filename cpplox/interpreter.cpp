#include "./interpreter.h"
#include "loxCallable.h"
std::shared_ptr<Environment> environment = std::make_shared<Environment>();

struct InterpreterHelper::loxTypesToBool {
  bool operator()(double value) const { return value; }

  bool operator()(const std::string &value) const { return value != "0"; }

  bool operator()(std::monostate) const { return false; }

  bool operator()(int value) const { return value; }

  bool operator()(bool value) const { return value; }
};

struct Interpreter { // Visitor for Expr
  loxTypes operator()(std::shared_ptr<Assign> expr) {
    loxTypes value = InterpreterHelper::evaluate(expr->right);
    environment->assign(expr->left, value);
    return value;
  }

  loxTypes operator()(std::shared_ptr<Literal> expr) { return expr->value; }

  loxTypes operator()(std::shared_ptr<Grouping> expr) {
    return InterpreterHelper::evaluate(expr->expression);
  }

  loxTypes operator()(std::shared_ptr<Unary> expr) {
    loxTypes right = InterpreterHelper::evaluate(expr->right);

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
  loxTypes operator()(std::shared_ptr<Binary> expr) {
    loxTypes left = InterpreterHelper::evaluate(expr->left);
    loxTypes right = InterpreterHelper::evaluate(expr->right);

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
  loxTypes operator()(std::shared_ptr<Variable> expr) {
    return environment->get(expr->name);
  }
  loxTypes operator()(std::shared_ptr<Logical> expr) {
    loxTypes left = InterpreterHelper::evaluate(expr->left);

    if (expr->op.type == OR) {
      if (std::visit(InterpreterHelper::loxTypesToBool{}, left)) {
        return left;
      } else {
        if (!std::visit(InterpreterHelper::loxTypesToBool{}, left)) {
          return left;
        }
      }
    }
    return InterpreterHelper::evaluate(expr->right);
  }
  loxTypes operator()(std::shared_ptr<Call> expr) {
    loxTypes callee = InterpreterHelper::evaluate(expr->callee);

    std::vector<loxTypes> arguments;

    for (Expr argument : expr->arguments) {
      arguments.push_back(InterpreterHelper::evaluate(argument));
    }

    // Cast here
    LoxCallable function; // Cast callee to LoxCallable
    if (arguments.size() != function.arity()) {
      throw new std::runtime_error(
          "Expected " + std::to_string(function.arity()) +
          " arguments but got " + std::to_string(arguments.size()) + ".");
    }
  }
};

struct InterpreterStmt {
  void operator()(std::shared_ptr<Expression> stmt) {
    InterpreterHelper::evaluate(stmt->expression);
  }
  void operator()(std::shared_ptr<Print> stmt) {
    loxTypes value = InterpreterHelper::evaluate(stmt->expression);
    std::cout << Token::literalToString(value) << std::endl;
  }
  void operator()(std::shared_ptr<Var> stmt) {
    loxTypes value;
    if (stmt->initializer.has_value()) {
      value = InterpreterHelper::evaluate(stmt->initializer.value());
    } else {
      value = std::monostate{};
    }
    environment->define(stmt->name.lexeme, value);
  }
  void operator()(std::shared_ptr<Block> stmt) {
    std::shared_ptr<Environment> environmentInside =
        std::make_shared<Environment>(environment);

    executeBlock(stmt->statements, environmentInside);
  }
  void operator()(std::shared_ptr<If> stmt) {
    if (std::visit(InterpreterHelper::loxTypesToBool{},
                   InterpreterHelper::evaluate(stmt->condition))) {
      InterpreterHelper::interpret({stmt->thenBranch});
    } else {
      if (stmt->elseBranch.has_value()) {
        InterpreterHelper::interpret({stmt->elseBranch.value()});
      }
    }
  }
  void operator()(std::shared_ptr<While> stmt) {
    while (std::visit(InterpreterHelper::loxTypesToBool{},
                      InterpreterHelper::evaluate(stmt->condition))) {
      InterpreterHelper::interpret({stmt->body});
    }
  }
};

void executeBlock(std::vector<Stmt> statements,
                  std::shared_ptr<Environment> newEnvironment) {
  std::shared_ptr<Environment> previous;
  previous = environment;
  try {
    environment = newEnvironment;
    for (Stmt statement : statements) {
      std::visit(InterpreterStmt{}, statement);
    }
    environment = previous;
  } catch (std::exception &e) {
    std::cerr << "Caught exception " << e.what() << std::endl;
  }
}

loxTypes InterpreterHelper::evaluate(Expr expr) {
  return std::visit(Interpreter{}, expr);
}

void InterpreterHelper::interpret(std::vector<Stmt> stmts) {
  for (Stmt stmt : stmts) {
    std::visit(InterpreterStmt{}, stmt);
  }
}
