#include <stdio.h>
#include <stdlib.h>


char* file_parser(const char* filename) {

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("ERROR: File not found and/or unable to open (EF0)");
        return NULL;
    }
    fseek(file, 0, SEEK_END); //Moves the cursor to the end of the file
    long fsize = ftell(file); //Finds the cursor position and translates it into bytes size
    fseek(file, 0, SEEK_SET); //Moves the cursor to the start of the file

    //Generates an array with a size of bytes equal to the size of the file and adds 1 free cell for a NULL
    char *buffer = malloc(fsize + 1);

    if (buffer == NULL) {
        perror("ERROR: Memory Allocation (EF1) ");
        fclose(file);
        return NULL;
    }
    size_t readf = fread(buffer, 1, fsize, file);
    if (readf != fsize) {
        perror("ERROR: File read error (EF2) ");
        free(buffer);
        fclose(file);
        return NULL;
    }
    buffer[fsize] = '\0';
    fclose(file);
    return buffer;

}
