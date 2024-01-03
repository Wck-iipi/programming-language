set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
project(cpplox)

set(SOURCE_FILES
  main.cpp
  scanner.cpp
  error.cpp
  token.cpp
  Expr.cpp
  # tools/ASTPrinter.cpp
  parser.cpp
  interpreter.cpp
  Stmt.cpp
  environment.cpp
  loxCallable.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
