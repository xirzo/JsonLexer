#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "token.h"

void lex(const char* test_name, const char* json, const Token* expected,
         size_t expected_size) {
    struct Lexer lexer;
    init_lexer(&lexer, json);

    for (size_t i = 0; i < expected_size; ++i) {
        Token token = next_token(&lexer);

        if (token.type != expected[i].type) {
            fprintf(stderr,
                    "Assertion failed in %s at index %zu\n"
                    "expected: %d, got: %d\nCurrent char is %c\n",
                    test_name, i, expected[i].type, token.type, lexer.current_char);

            assert(token.type == expected[i].type);
        }

        if (strcmp(token.literal, expected[i].literal) != 0) {
            fprintf(stderr,
                    "Assertion failed in %s at index %zu\n"
                    "expected: %s, got: %s\n",
                    test_name, i, expected[i].literal, token.literal);

            assert(strcmp(token.literal, expected[i].literal) == 0);
        }
    }
}

void test_lex_empty_object() {
    const char* json = "{}";

    const Token expected[] = {
        {TOKEN_LBR, "{"},
        {TOKEN_RBR, "}"},
    };

    size_t expected_size = sizeof(expected) / sizeof(expected[0]);

    lex("test_lex_empty_object", json, expected, expected_size);

    printf("test_lex_empty_object passed!\n");
}

void test_lex_key_number() {
    const char* json = "{\"key\": 123}";

    const Token expected[] = {
        {TOKEN_LBR, "{"},      {TOKEN_STRING, "key"}, {TOKEN_COLON, ":"},
        {TOKEN_NUMBER, "123"}, {TOKEN_RBR, "}"},      {TOKEN_EOF, ""},
    };

    size_t expected_size = sizeof(expected) / sizeof(expected[0]);

    lex("test_lex_key_number", json, expected, expected_size);

    printf("test_lex_key_number passed!\n");
}

void test_lex_key_string() {
    const char* json = "{\"key\": \"value\"}";

    const Token expected[] = {

        {TOKEN_LBR, "{"},        {TOKEN_STRING, "key"}, {TOKEN_COLON, ":"},
        {TOKEN_STRING, "value"}, {TOKEN_RBR, "}"},      {TOKEN_EOF, ""},
    };

    size_t expected_size = sizeof(expected) / sizeof(expected[0]);

    lex("test_lex_key_string", json, expected, expected_size);

    printf("test_lex_key_string passed!\n");
}

void test_lex_key_boolean() {
    const char* json = "{\"key\": true}";

    const Token expected[] = {

        {TOKEN_LBR, "{"},        {TOKEN_STRING, "key"}, {TOKEN_COLON, ":"},
        {TOKEN_BOOLEAN, "true"}, {TOKEN_RBR, "}"},      {TOKEN_EOF, ""},
    };

    size_t expected_size = sizeof(expected) / sizeof(expected[0]);

    lex("test_lex_key_boolean", json, expected, expected_size);

    printf("test_lex_key_boolean passed!\n");
}

void test_lex_key_null() {
    const char* json = "{\"key\": null}";

    const Token expected[] = {

        {TOKEN_LBR, "{"},     {TOKEN_STRING, "key"}, {TOKEN_COLON, ":"},
        {TOKEN_NULL, "null"}, {TOKEN_RBR, "}"},      {TOKEN_EOF, ""},
    };

    size_t expected_size = sizeof(expected) / sizeof(expected[0]);

    lex("test_lex_key_null", json, expected, expected_size);

    printf("test_lex_key_boolean passed!\n");
}

int main() {
    test_lex_empty_object();
    test_lex_key_number();
    test_lex_key_string();
    test_lex_key_boolean();
    test_lex_key_null();

    printf("All tests passed!\n");
    return 0;
}
