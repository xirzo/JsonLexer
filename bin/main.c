#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"

int main() {
    const char* test_jsons[] = {
        "{\"key\": \"value\"}",
        "{\"key1\": \"value1\", \"key2\": 42, \"key3\": true}",
        "{\"key\": {\"nested_key\": \"nested_value\"}}",
        "{\"key\": [1, 2, 3]}",
    };

    size_t num_jsons = sizeof(test_jsons) / sizeof(test_jsons[0]);

    for (size_t i = 0; i < num_jsons; i++) {
        printf("Testing JSON %zu: %s\n", i + 1, test_jsons[i]);

        struct Lexer lexer;
        init_lexer(&lexer, test_jsons[i]);

        Token* token;

        while ((token = next_token(&lexer))->type != TOKEN_EOF) {
            printf("  %s, %s\n", token_type_to_string(token->type), token->literal);
        }

        printf("\n");
    }

    return EXIT_SUCCESS;
}
