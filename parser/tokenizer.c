#include <string.h>
#include "tokenizer.h"
#include <stdlib.h>

static char *current_token = NULL;
static int nx_token = 0;


struct context {
    char *current_token;

};

void token_init(char *resource) {
    nx_token = 0;
    current_token = resource;


    if (*current_token == '<') {
        if (*(current_token+1) == '/') {
            nx_token = 2;
            current_token +=2;
        }
        else if (*(current_token+1) == '!') {
            nx_token = 3;
            current_token ++;
        }
        else {
            nx_token = 1;
            current_token++;
        }
    }
}

char* type_parser(Token *t, token_type type, char* type_ptr, int nx ) {
    t->type = type;
    t->input = type_ptr;
    //Checks the end of the ELEMENT
    char *end = strchr(type_ptr, '>');
    if (end != NULL) {
        *end = '\0';
        type_ptr = end + 1; // Moves the pointer 1 after the end of the Tag
        //Check of the next char and the type of the Element
        if (*type_ptr == '<') {
            type_ptr++;
            if (*type_ptr == '!') {
                nx_token = 3;
                type_ptr ++;
            }
            else if (*type_ptr == '/') {
                nx_token = 2;
                type_ptr ++;
            }
            else {
                nx_token = 1;

            }
        } else {
            nx_token = 0;
        }
    }
    else {
        //Error Handler: If the Tag isn't closed it stops it automatically
        type_ptr = NULL;
    }
    return type_ptr;
}

Token token_parser() {
    Token token;
    token.input = NULL;
    token.type = END_OF_TOKEN;

    if (current_token == NULL || *current_token == '\0') {
        return token;
    }
    //Check if the Element it's a TAG(1) or TEXT (0)
    if (nx_token == 1) {
        //Checks the end of the ELEMENT
        current_token = type_parser(&token, O_TAG_TOKEN, current_token, nx_token);

    }
    else if (nx_token == 2) {
        current_token = type_parser(&token, C_TAG_TOKEN, current_token, nx_token);

    }
    else if (nx_token == 3) {
        current_token = type_parser(&token, DOCTYPE_TOKEN, current_token, nx_token);

    }
    else {
        token.type = TEXT_TOKEN;
        token.input = current_token;
        //Parses the text till the start of a new TAG
        char *end = strchr(current_token, '<');
        if (end != NULL) {
            *end = '\0'; // End text string
            current_token = end + 1; // Move past the '<'
            if (*current_token == '/') {
                nx_token = 2;       // It's a Closing Tag
                current_token++;    // Move past '/'
            } else {
                nx_token = 1;       // It's an Opening Tag
            }
        }else {
            //If no more tags are found everything is parsed as Text
            current_token += strlen(current_token);
        }


    }

    return token;
}