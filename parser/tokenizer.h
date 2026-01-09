#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum token_type {
    TEXT_TOKEN,
    O_TAG_TOKEN,
    C_TAG_TOKEN,
    END_OF_TOKEN,
    DOCTYPE_TOKEN,
}token_type;

typedef struct token {
    char *input;
    token_type type;
} Token;

void tokenize(char *input);

Token next_token();
//TODO: ERROR MAKER

#endif
