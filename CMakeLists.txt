cmake_minimum_required(VERSION 3.30.5)

project(
  json_lexer
  VERSION 1.0
  DESCRIPTION "Just a small JSON lexer"
  LANGUAGES C)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)
