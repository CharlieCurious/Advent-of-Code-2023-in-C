#include <errno.h>
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *open_file_or_exit(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Failed to open input file.");
        exit(EXIT_FAILURE);
    }
}

StringArray *read_lines(FILE *fp, int max_lines, int max_length) {
    FILE *file;
    char buffer[max_length];
    
    char **lines = malloc(max_lines * sizeof(char *));
    if (lines == NULL) {
        perror("Error allocating lines.");
        return NULL;
    }

    unsigned int count = 0;
    while (fgets(buffer, max_length, fp)) {
        if (count >= max_lines) {
            printf("Maximum number of lines (%d) exceeded.\n", max_lines);
            break;
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (len == 0) {
            continue;
        }

        lines[count] = malloc(len + 1);
        if (lines[count] == NULL) {
            perror("Failed to allocate memory for line.");
            goto cleanup;
        }
        
        strcpy(lines[count], buffer);
        count++;
    }

    StringArray *array = malloc(sizeof(StringArray));
    if (array == NULL) {
        perror("Error allocating StringArray.");
        goto cleanup;
    }
    array->strings = lines;
    array->size = count;

    return array;

cleanup:
    if (lines != NULL) {
        for (size_t i = 0; i < count; i++) {
            if (lines[i] != NULL) {
                free(lines[i]);
            }
        }
        free(lines);
    }
    return NULL;
}

void free_string_array(StringArray *array) {
    if (array == NULL) {
        return;
    }
    for (size_t i = 0; i < array->size; i++) {
        if (array->strings[i] != NULL) {
            free(array->strings[i]);
        }
    }
    if (array->strings != NULL) {
        free(array->strings);
    }
    free(array);
}