#ifndef TOKEH_H
#define TOKEH_H

typedef enum {
    TOKEN_ILLEGAL = -1,
    TOKEN_EOF = 0,

    TOKEN_LBR = 1,
    TOKEN_RBR = 2,
    TOKEN_LSQBR = 3,
    TOKEN_RSQBR = 4,

    TOKEN_COLON = 5,
    TOKEN_COMMA = 6,

    TOKEN_STRING = 7,
    TOKEN_NUMBER = 8,
    TOKEN_BOOLEAN = 9,
    TOKEN_NULL = 10,
} TokenType;

typedef struct {
    TokenType type;
    const char* literal;
} Token;

void init_token(Token* token, const char* literal, TokenType type);

const char* token_type_to_string(TokenType type);

#endif  // !TOKEH_H
