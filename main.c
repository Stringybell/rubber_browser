#include <stdio.h>
#include "parser/tokenizer.h"

void token_init(char *resource);
char* file_parser(const char* filename);

Token token_parser();

int main() {
    // Note: We use a mutable array [], not a pointer *,
    // because the tokenizer modifies the string (inserts \0).
    char filename[]= "parser/test_file.html";

    char* html = file_parser(filename);


    printf("Parsing: %s\n\n", filename); // Warning: this prints only until the first \0 if modified, so we print before init.

    token_init(html);

    Token token = token_parser();
    while (token.type != END_OF_TOKEN) {
        if (token.type == O_TAG_TOKEN ) {
            printf("[O_TAG]: %s\n", token.input);
        }
        else if (token.type == C_TAG_TOKEN) {
            printf("[C_TAG]: %s\n", token.input);
        }
        else if (token.type == TEXT_TOKEN) {
            printf("[TXT]: %s\n", token.input);
        }
        else if (token.type == DOCTYPE_TOKEN) {
            printf("[DOC]: %s\n", token.input);
        }

        token = token_parser();
    }

    return 0;
}