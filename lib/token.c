#include "token.h"

void init_token(Token* token, const char* literal, TokenType type) {
    token->literal = literal;
    token->type = type;
}

const char* token_type_to_string(TokenType type) {
    const char* token_names[] = {
        "TOKEN_EOF",    "TOKEN_LBR",     "TOKEN_RBR",   "TOKEN_LSQBR",
        "TOKEN_RSQBR",  "TOKEN_COLON",   "TOKEN_COMMA", "TOKEN_STRING",
        "TOKEN_NUMBER", "TOKEN_BOOLEAN", "TOKEN_NULL",
    };

    if (type >= 0 && type <= 10) {
        return token_names[type];
    } else if (type == TOKEN_ILLEGAL) {
        return "TOKEN_ILLEGAL";
    }

    return "UNKNOWN_TOKEN";
}
