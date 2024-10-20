#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "input_reader.h"

char **read_lines(char *filename, int max_lines, int max_length) {
    FILE *file;
    char **lines = (char **)malloc(max_lines * sizeof(char *));
    char buffer[max_length];

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s: %s\n", filename, strerror(errno));
    }

    int count = 0;
    while (fgets(buffer, max_length, file)) {
        if (count >= max_lines) {
            printf("Maximum number of lines (%d) exceeded.\n", max_lines);
            break;
        }

        lines[count] = (char *)malloc(strlen(buffer) + 1);
        if (lines[count] == NULL) {
            fprintf(stderr, "Failed to allocate memory for line: %s.\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        strcpy(lines[count], buffer);
        count++;
    }

    fclose(file);
    return lines;
}

size_t len(char **array) {
    return sizeof(array) / sizeof(char *);
}