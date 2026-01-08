#include <string.h>
#include <stdio.h>
#include "tokenizer.h"
#include <stdlib.h>

static char *current_token = NULL;
static int nx_token = 0;

char* file_parser(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("ERROR: File not found and/or unable to open");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)malloc(fsize + 1);
    if (buffer == NULL) {
        perror("ERROR: Memory Allocation");
        free(buffer);
        fclose(file);
        return NULL;
    }
    size_t readf = fread(buffer, 1, fsize, file);
    if (readf != fsize) {
        perror("ERROR: File read error");
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[fsize] = '\0';
    fclose(file);
    return buffer;

}

struct context {
    char *current_token;

};

void token_init(char *resource) {
    nx_token = 0;
    current_token = resource;
    if (*current_token == '<') {
        nx_token = 1;
        current_token++;
    }
}
Token mktoken() {
    Token token;
    token.input = NULL;
    token.type = END_OF_TOKEN;

    if (current_token == NULL || *current_token == '\0') {
        return token;
    }
    //Check if the Element it's a TAG(1) or TEXT (0)
    if (nx_token == 1) {
        token.type = TAG_TOKEN;
        token.input = current_token;
        //Checks the end of the ELEMENT
        char *end = strchr(current_token, '>');
        if (end != NULL) {
            *end = '\0';
            current_token = end + 1; // Moves the pointer 1 after the end of the Tag
            //Check of the next char and the type of the Element
            if (*current_token == '<') {
                nx_token = 1;
                current_token++;
            } else {
                nx_token = 0;
            }
        }
        else {
            //Error Handler: If the Tag isn't closed it stops it automatically
            current_token = NULL;
        }


    }
    else {
        token.type = TEXT_TOKEN;
        token.input = current_token;
        //Parses the text till the start of a new TAG
        char *end = strchr(current_token, '<');
        if (end != NULL) {
            *end = '\0'; // End text string
            current_token = end + 1; // Move past the '<'
            nx_token = 1;
        }else {
            //If no more tags are found everything is parsed as Text
            current_token += strlen(current_token);
        }


    }

    return token;

}