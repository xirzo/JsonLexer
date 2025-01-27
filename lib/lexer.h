#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stddef.h>

#include "token.h"

struct Lexer {
    const char* input;
    size_t input_len;
    char current_char;
    size_t current_position;
    size_t read_position;
};

void init_lexer(struct Lexer* lexer, const char* input);

void read_char(struct Lexer* lexer);

bool is_whitespace(char ch);

void skip_whitespaces(struct Lexer* lexer);

void parse_string(struct Lexer* lexer, Token* token);

void parse_number(struct Lexer* lexer, Token* token);

void parse_boolean(struct Lexer* lexer, Token* token);

void parse_null(struct Lexer* lexer, Token* token);

Token* next_token(struct Lexer* lexer);

#endif  // !LEXER_H
