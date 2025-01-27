#include "lexer.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

void init_lexer(struct Lexer* lexer, const char* input) {
    lexer->input = input;
    lexer->input_len = strlen(input);
    lexer->current_position = 0;
    lexer->read_position = 0;
    lexer->current_char = '\0';

    read_char(lexer);
}

void read_char(struct Lexer* lexer) {
    if (lexer->read_position >= lexer->input_len) {
        lexer->current_char = '\0';
    } else {
        lexer->current_char = lexer->input[lexer->read_position];
    }

    lexer->current_position = lexer->read_position;
    lexer->read_position++;
}

bool is_whitespace(char ch) {
    switch (ch) {
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
        case ' ':
            return true;
        default:
            return false;
    }
}

void skip_whitespaces(struct Lexer* lexer) {
    while (is_whitespace(lexer->current_char)) {
        read_char(lexer);
    }
}

void parse_string(struct Lexer* lexer, Token* token) {
    read_char(lexer);
    size_t start_pos = lexer->current_position;

    while (lexer->current_char != '"') {
        read_char(lexer);
    }

    size_t end_pos = lexer->current_position;
    size_t len = end_pos - start_pos;

    char* literal = malloc(sizeof(char[len]));

    size_t i = 0;

    for (size_t j = start_pos; j < end_pos; ++j) {
        literal[i] = lexer->input[j];
        ++i;
    }

    init_token(token, literal, TOKEN_STRING);
}

void parse_number(struct Lexer* lexer, Token* token) {
    size_t start_pos = lexer->current_position;

    for (size_t i = start_pos + 1; i < lexer->input_len; ++i) {
        if (lexer->input[i] == ',' || lexer->input[i] == '}' || lexer->input[i] == '\0') {
            break;
        }

        read_char(lexer);
    }

    size_t end_pos = lexer->current_position + 1;
    size_t len = end_pos - start_pos;

    char* literal = malloc(sizeof(char[len]));

    size_t i = 0;

    for (size_t j = start_pos; j < end_pos; ++j) {
        literal[i] = lexer->input[j];
        ++i;
    }

    init_token(token, literal, TOKEN_NUMBER);
}

void parse_boolean(struct Lexer* lexer, Token* token) {
    size_t start_pos = lexer->current_position;

    for (size_t i = start_pos + 1; i < lexer->input_len; ++i) {
        if (lexer->input[i] == ',' || lexer->input[i] == '}' || lexer->input[i] == '\0') {
            break;
        }

        read_char(lexer);
    }

    size_t end_pos = lexer->current_position + 1;
    size_t len = end_pos - start_pos;

    char* literal = malloc(sizeof(char[len]));

    size_t i = 0;

    for (size_t j = start_pos; j < end_pos; ++j) {
        literal[i] = lexer->input[j];
        ++i;
    }

    init_token(token, literal, TOKEN_BOOLEAN);
}

void parse_null(struct Lexer* lexer, Token* token) {
    size_t start_pos = lexer->current_position;
    size_t end_pos = lexer->current_position + 4;
    size_t len = end_pos - start_pos;

    char* literal = malloc(sizeof(char[len]));

    size_t i = 0;

    for (size_t j = start_pos; j < end_pos; ++j) {
        literal[i] = lexer->input[j];
        ++i;
    }

    if (strcmp(literal, "null") != 0) {
        init_token(token, "", TOKEN_ILLEGAL);
        return;
    }

    read_char(lexer);
    read_char(lexer);
    read_char(lexer);

    init_token(token, "null", TOKEN_NULL);
}

Token* next_token(struct Lexer* lexer) {
    Token* token;

    skip_whitespaces(lexer);

    switch (lexer->current_char) {
        case '\0': {
            init_token(token, "\0", TOKEN_EOF);
            break;
        }

        case '{': {
            init_token(token, "{", TOKEN_LBR);
            break;
        }

        case '}': {
            init_token(token, "}", TOKEN_RBR);
            break;
        }

        case '[': {
            init_token(token, "[", TOKEN_LSQBR);
            break;
        }

        case ']': {
            init_token(token, "]", TOKEN_RSQBR);
            break;
        }

        case ':': {
            init_token(token, ":", TOKEN_COLON);
            break;
        }

        case ',': {
            init_token(token, ",", TOKEN_COMMA);
            break;
        }

        case '"': {
            parse_string(lexer, token);
            break;
        }

        case 't':
        case 'f': {
            parse_boolean(lexer, token);
            break;
        }

        case 'n': {
            parse_null(lexer, token);
            break;
        }

        default: {
            if (isdigit(lexer->current_char)) {
                parse_number(lexer, token);
                break;
            }
        }
    }

    read_char(lexer);
    return token;
}
