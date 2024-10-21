#pragma once

typedef struct {
    char **strings;
    unsigned int size;
} StringArray;

// Given a file name, returns an array or strings
// where each element is a line from the file.
StringArray *read_lines(char *filename, int max_lines, int max_length);

void free_string_array(StringArray *array);