#include <stdio.h>
#include "parser/tokenizer.h"
void token_init(char *resource);
char* file_parser(const char* filename);
Token mktoken();
int main() {
    // Note: We use a mutable array [], not a pointer *,
    // because the tokenizer modifies the string (inserts \0).
    char filename[]= "parser/test_file.html";

    char* html = file_parser(filename);


    printf("Parsing: %s\n\n", filename); // Warning: this prints only until the first \0 if modified, so we print before init.

    token_init(html);

    Token tok = mktoken();
    while (tok.type != END_OF_TOKEN) {
        if (tok.type == TAG_TOKEN) {
            printf("[TAG]: %s\n", tok.input);
        } else if (tok.type == TEXT_TOKEN) {
            printf("[TXT]: %s\n", tok.input);
        }

        tok = mktoken();
    }

    return 0;
}