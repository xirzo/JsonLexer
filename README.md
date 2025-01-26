# JSON Lexer 📄🔍

![Build Status](https://camo.githubusercontent.com/<your-build-status-badge-url>/badge/build-passing-brightgreen)  
![Tests](https://camo.githubusercontent.com/<your-tests-badge-url>/badge/tests%20%E2%9C%94%EF%B8%8F%20passing-brightgreen)  
![License](https://camo.githubusercontent.com/<your-license-badge-url>/badge/license-MIT-blue)  

This is a simple lexer written in C that tokenizes JSON files. It breaks down JSON input into tokens, making it easier to parse and process data. 🚀

---

## How It Works 🛠️

The lexer reads a JSON string character by character and identifies tokens based on the JSON syntax. It uses a `Lexer` struct to keep track of the current state and a `Token` struct to represent each token.

### Key Functions

- `init_lexer`: Initializes the lexer with the input JSON string.
- `next_token`: Returns the next token in the input.

---

## Token Types 🏷️

The lexer recognizes the following token types:

| Token Type   | Example       | Description                          |
|--------------|---------------|--------------------------------------|
| `TOKEN_LBR`  | `{`           | Left brace                           |
| `TOKEN_RBR`  | `}`           | Right brace                          |
| `TOKEN_COLON`| `:`           | Colon                                |
| `TOKEN_COMMA`| `,`           | Comma                                |
| `TOKEN_STRING`| `"key"`      | String literal                       |
| `TOKEN_NUMBER`| `123`        | Number literal                       |
| `TOKEN_BOOLEAN`| `true`/`false` | Boolean literal                   |
| `TOKEN_NULL` | `null`        | Null literal                         |
| `TOKEN_EOF`  | N/A           | End of file/input                    |
| `TOKEN_ILLEGAL`| N/A        | Illegal/unknown token                |

---

## Example Usage 🖥️

Here’s how you can use the lexer in your code:

```c
#include "lexer.h"

int main() {
    const char* json = "{\"key\": \"value\"}";
    struct Lexer lexer;
    init_lexer(&lexer, json);

    Token token;

    do {
        token = next_token(&lexer);
        printf("Token: %s, Literal: %s\n", token_type_to_string(token.type), token.literal);
    } while (token.type != TOKEN_EOF);

    return 0;
}
```

---

## Running Tests 🧪

The project includes a suite of tests to verify the lexer's functionality. Run the tests to ensure everything works as expected:

### Test Cases

1. **Empty Object** `{}` ✅
2. **Key-Number Pair** `{"key": 123}` ✅
3. **Key-String Pair** `{"key": "value"}` ✅
4. **Key-Boolean Pair** `{"key": true}` ✅
5. **Key-Null Pair** `{"key": null}` ✅

---

## Project Structure 📂

```
json-lexer/
├── lexer.h          # Lexer header file
├── lexer.c          # Lexer implementation
├── token.h          # Token header file
├── token.c          # Token implementation
├── main.c           # Main program and tests
```
