#pragma once

#include <stdlib.h>

// Given a file name, returns an array or strings
// where each element is a line from the file.
char **read_lines(char *filename, int max_lines, int max_length);

// Returns the number of elements in array of strings.
size_t len(char **array);
