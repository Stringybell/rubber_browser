#include <stdio.h>
#include "tokenizer.h"
void token_init(char *resource);
Token mktoken();
int main() {
    // Note: We use a mutable array [], not a pointer *,
    // because the tokenizer modifies the string (inserts \0).
    char html[] = "<div>Hello World</div>";

    printf("Parsing: %s\n\n", html); // Warning: this prints only until the first \0 if modified, so we print before init.

    token_init(html);

    Token tok = mktoken();
    while (tok.type != END_OF_TOKEN) {
        if (tok.type == TAG_TOKEN) {
            printf("[TAG]: %s\n", tok.input);
        } else if (tok.type == TEXT_TOKEN) {
            printf("[TXT]: %s\n", tok.input);
        }

        t = mktoken();
    }

    return 0;
}