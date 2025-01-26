cmake_minimum_required(VERSION 3.30.5)

project(
  json_lexer
  VERSION 1.0
  DESCRIPTION "Just a small JSON lexer"
  LANGUAGES C)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(lexer
    lib/lexer.c
    lib/lexer.h
    lib/token.c
    lib/token.h
)

target_include_directories(lexer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")

install(TARGETS lexer DESTINATION lib)
install(FILES lib/lexer.h lib/token.h DESTINATION include)

add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)
