# cpplox: A Tree-Walk Interpreter for Lox in C++

This project implements a tree-walk interpreter for the Lox programming language, as defined in the book "Crafting Interpreters" by Robert Nystrom. The book is in Java but current implementation is in C++ without using LLVM. 

## Features

- **Lexical Analysis (Scanning):** Converts the source code into a stream of tokens using the `Scanner` class.
- **Syntactic Analysis (Parsing):**  Constructs an Abstract Syntax Tree (AST) from the tokens using the `Parser` class, employing a recursive descent parsing strategy.
- **AST Generation:**  The `generateAST` tool automatically generates C++ classes representing the different node types in the AST based on a simplified grammar definition.
- **Tree-Walk Interpretation:** The `Interpreter` class traverses the AST, executing the corresponding code for each node type.
- **Environment Handling:** The `Environment` class manages variable bindings, supporting scoping rules.
- **Error Handling:**  The `Error` namespace provides functionality to report errors encountered during parsing or interpretation, including line numbers and error messages.
- **AST Printing:** The `ASTPrinter` aids in debugging by providing a textual representation of the generated AST. 

## Implementation Details

- The code is structured into multiple files for better organization and maintainability.
- The project leverages modern C++ features, including `std::variant` for representing different AST node types and `std::optional` for optional values.

## Future Work

- Implement more advanced Lox features, such as control flow statements, functions, and classes.
- Consider adding a bytecode compiler and a virtual machine for improved performance.
- Enhance the error reporting mechanism with more descriptive error messages and better error recovery. 
- Implement a standard library of Lox functions for common tasks.
- Develop a testing framework for unit testing and integration testing. 
