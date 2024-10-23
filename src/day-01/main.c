#include <ctype.h>
#include <lib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

unsigned int process_line(char *line);

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file.");
        exit(EXIT_FAILURE);
    }

    StringArray *lines = read_lines(fp, 1001, 128);
    fclose(fp);

    unsigned int sum = 0;
    for (size_t i = 0; i < lines->size; i++) {
        sum += process_line(lines->strings[i]);
    }

    printf("Answer is: %d\n", sum);
    free_string_array(lines);
    return EXIT_SUCCESS;
}

unsigned int process_line(char *line) {
    size_t left_index = 0;
    size_t right_index = strlen(line) - 1;

    printf("Line value: %s\n", line);

    char number[2] = "00";
    printf("Chars value is %s\n", number);
    bool is_left_number_found = false;
    bool is_right_number_found = false;
    while (left_index <= right_index) {

        if (isdigit(line[left_index]) && !is_left_number_found) {
            number[0] = line[left_index];
            is_left_number_found = true;
        } else {
            left_index++;
        }

        if (isdigit(line[right_index]) && !is_right_number_found) {
            number[1] = line[right_index];
            is_right_number_found = true;
        } else {
            right_index--;
        }
    }
    printf("line: %s\n", number);
    return atoi(number);
}