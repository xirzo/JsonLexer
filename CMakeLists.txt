cmake_minimum_required(VERSION 3.30.5)

project(
  json_lexer
  VERSION 1.0
  DESCRIPTION "Just a small JSON lexer"
  LANGUAGES C)

set(CMAKE_CXX_STANDARD_REQUIRED True)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)

file(GLOB PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/lib/*.h")
foreach(header ${PUBLIC_HEADERS})
    file(COPY ${header} DESTINATION ${CMAKE_BINARY_DIR}/include)
endforeach()

add_library(lexer SHARED
    lib/lexer.c
    lib/token.c
)

add_library(json::lexer ALIAS lexer)

target_include_directories(lexer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS lexer
        EXPORT lexerTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)

install(DIRECTORY ${CMAKE_BINARY_DIR}/include/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

install(EXPORT lexerTargets
        FILE lexerConfig.cmake
        NAMESPACE json::
        DESTINATION lib/cmake/lexer)

add_subdirectory(bin)
enable_testing()
add_subdirectory(tests)
