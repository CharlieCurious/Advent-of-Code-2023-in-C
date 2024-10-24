#include <ctype.h>
#include <lib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

unsigned int process_line(const char *line);

int main(int argc, char **argv) {
    if (argc < 2) {
        puts("Provide a puzzle input file.");
        exit(EXIT_FAILURE);
    }

    FILE *fp = open_file_or_exit(argv[1]);

    StringArray *lines = read_lines(fp, 1001, 128);
    fclose(fp);

    unsigned int sum = 0;
    for (size_t i = 0; i < lines->size; i++) {
        sum += process_line(lines->strings[i]);
    }

    printf("Answer is: %u\n", sum);
    free_string_array(lines);
    return EXIT_SUCCESS;
}

unsigned int process_line(const char *line) {
    size_t left_index = 0;
    size_t right_index = strlen(line) - 1;

    char number[3] = "00";  // 3 to account for null terminator.
    bool is_left_number_found = false;
    bool is_right_number_found = false;
    while (left_index <= right_index) {

        if (!is_left_number_found) {
            if (isdigit(line[left_index])) {
                number[0] = line[left_index];
                is_left_number_found = true;
            } else {
                left_index++;
            }
        }

        if (!is_right_number_found) {
            if (isdigit(line[right_index])) {
                number[1] = line[right_index];
                is_right_number_found = true;
            } else {
                right_index--;
            }
        }

        if (is_left_number_found && is_left_number_found) break;
    }
    return atoi(number);
}