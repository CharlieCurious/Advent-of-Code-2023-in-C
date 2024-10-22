#include <lib.h>
#include <stdlib.h>
#include <unity.h>

FILE *create_test_file(const char *file_content);

char *file_content = "Hello, Charlie.\nYou want biscuitini?\nTuna snack?";

FILE *create_test_file(const char *file_content) {
    FILE *fp = tmpfile();
    fputs(file_content, fp);
    rewind(fp);
    return fp;
}

void setUp() {
}

void tearDown() {
}

void test_read_lines_stringarray_should_have_correct_size(void) {
    FILE *fp = create_test_file(file_content);

    StringArray *result = read_lines(fp, 100, 100);
    fclose(fp);

    TEST_ASSERT_EQUAL(3, result->size);
    free_string_array(result);
}

void test_read_lines_stringarray_should_have_correct_strings(void) {
    FILE *fp = create_test_file(file_content);

    StringArray *result = read_lines(fp, 100, 100);
    fclose(fp);

    TEST_ASSERT_EQUAL_CHAR_ARRAY("Hello, Charlie.", result->strings[0], 15);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("You want biscuitini?", result->strings[1], 20);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Tuna snack?", result->strings[2], 12);
    free_string_array(result);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_read_lines_stringarray_should_have_correct_size);
    RUN_TEST(test_read_lines_stringarray_should_have_correct_strings);

    return UNITY_END();
}