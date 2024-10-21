#include <lib.h>
#include <unity.h>

FILE *mock_fopen(const char *filename, const char *mode);
void *mock_malloc(size_t size);

#define fopen mock_fopen
#define malloc mock_malloc

// Mock control variables
int malloc_fail_after = -1;
int fopen_fail = 0;

FILE *mock_fopen(const char *filename, const char *mode) {
    if (fopen_fail) {
        return NULL;
    }
    return tmpfile();
}

void *mock_malloc(size_t size) {
    static int malloc_count = 0;
    malloc_count++;
    if (malloc_fail_after > 0 && malloc_count >= malloc_fail_after) {
        return NULL; // Simulate memory allocation after a specific point.
    }
    return malloc(size); // Normal malloc otherwise.
}

void setUp() {
    malloc_fail_after = -1;
    fopen_fail = 0;
}

void tearDown() {
}

void test_read_lines_file_open_failure(void) {
    fopen_fail = 1;

    StringArray *result = read_lines("nonexistent_file.txt", 10, 100);

    TEST_ASSERT_NULL(result);
}

void test_read_lines_lines_allocation_failure(void) {
    malloc_fail_after = 1; // Simulate malloc failure on the first call.

    StringArray *result = read_lines("test_file.txt", 10, 100);

    TEST_ASSERT_NULL(result);
}

void test_read_lines_individual_line_allocation_failure(void) {
    malloc_fail_after = 2; // Simulate malloc failure on the second malloc.

    StringArray *result = read_lines("test_file.txt", 10, 100);

    TEST_ASSERT_NULL(result);
}

void test_read_lines_stringarray_allocation_failure(void) {
    malloc_fail_after = 3; // Simulate malloc failure on the third malloc.

    StringArray *result = read_lines("test_file.txt", 10, 100);

    TEST_ASSERT_NULL(result);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_read_lines_file_open_failure);
    RUN_TEST(test_read_lines_lines_allocation_failure);
    RUN_TEST(test_read_lines_individual_line_allocation_failure);
    RUN_TEST(test_read_lines_stringarray_allocation_failure);

    return UNITY_END();
}