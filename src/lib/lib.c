#include <errno.h>
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


StringArray *read_lines(char *filename, int max_lines, int max_length) {
    FILE *file;
    char buffer[max_length];
    
    char **lines = malloc(max_lines * sizeof(char *));
    if (lines == NULL) {
        perror("Error allocating lines.");
        return NULL;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        goto cleanup;
    }

    unsigned int count = 0;
    while (fgets(buffer, max_length, file)) {
        if (count >= max_lines) {
            printf("Maximum number of lines (%d) exceeded.\n", max_lines);
            break;
        }

        lines[count] = malloc(strlen(buffer) + 1);
        if (lines[count] == NULL) {
            perror("Failed to allocate memory for line.");
            goto cleanup;
        }
        
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        strncpy(lines[count], buffer, max_length);
        count++;
    }

    StringArray *array = malloc(sizeof(StringArray));
    if (array == NULL) {
        perror("Error allocating StringArray.");
        goto cleanup;
    }
    array->strings = lines;
    array->size = count;

    fclose(file);
    return array;

cleanup:
    if (lines != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(lines[i]);
        }
        free(lines);
    }
    if (file != NULL) {
        fclose(file);
    }
    return NULL;
}

void free_string_array(StringArray *array) {
    if (array == NULL) {
        return;
    }
    for (size_t i = 0; i < array->size; i++) {
        free(array->strings[i]);
    }
    free(array->strings);
    free(array);
}