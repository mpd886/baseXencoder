#include <stdio.h>
#include <assert.h>
#include "baseX.h"

#define RANDOM_BYTES_TEST_FILE "random-bytes"
#define TOTAL_RANDOM_BYTES 72

typedef void (*test_func)();

#define TEST(x) { #x, x }
typedef struct {
    const char* name;
    test_func test;
} Test;    


typedef struct {
    int passed;
    int failed;
} Results;


static Results test_results = {0, 0};

void assertStringEquals(const char* expected, const char* result) {
    if (strcmp(expected, result) != 0) {
        printf("FAIL. Expected value %s does not match %s\n", expected, result);
        ++test_results.failed;
    } else {
        ++test_results.passed;
    }
}


void base64_encodeNoPadding() {
    const char* expected = "YWJj";
    const char* result = encode("abc", 3); 
    assertStringEquals(expected, result);
}


void base64_moreBytes() {
    const char* expected = "YWJjZGVm";
    const char* result = encode("abcdef", 6);
    assertStringEquals(expected, result);
}


void base64_onePaddingByte() {
    const char* expected = "YWJjZGU=";
    const char* result = encode("abcde", 5);
    assertStringEquals(expected, result);
}


void base64_twoPaddingByte() {
    const char* expected = "YWJjZA==";
    const char* result = encode("abcd", 4);
    assertStringEquals(expected, result);
}


void base64_encodeAlphabet() {
    const char* expected = "YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXo=";
    const char* result = encode("abcdefghijklmnopqrstuvwxyz", 26);
    assertStringEquals(expected, result);
}


void base64_encodeRandomBytes() {
    const char* expected = "zZKA1tUgPOn1LEx0QmZ2EhEIYYDPRqcR9H4SdPxPpsbivWUB1czwdJZDrGt9XDlYzQ4LAkU0RfPNvh6MMRR4RyCgrmBcwBIA";
    char input[TOTAL_RANDOM_BYTES] = {0};

    FILE* fp = fopen(RANDOM_BYTES_TEST_FILE, "rb");
    if (!fp) {
        perror(RANDOM_BYTES_TEST_FILE);
        fclose(fp);
        return;
    }
    fread(input, 1, TOTAL_RANDOM_BYTES, fp);
    fclose(fp);

    const char* result = encode(input, TOTAL_RANDOM_BYTES);

    assertStringEquals(expected, result);
}


int main() {
    int i;
    Test tests[] = {
        TEST(base64_encodeNoPadding),
        TEST(base64_moreBytes),
        TEST(base64_onePaddingByte),
        TEST(base64_twoPaddingByte),
        TEST(base64_encodeAlphabet),
        TEST(base64_encodeRandomBytes)
    };

    const int total_tests = sizeof(tests)/sizeof(tests[0]);

    for (i = 0 ; i <  total_tests ; ++i)  {
        printf("Testing %s...", tests[i].name);
        tests[i].test();
        printf("\n");
    }

    printf("\n%d tests passed\n%d tests failed\n", 
           test_results.passed, 
           test_results.failed);

    return 0;
}

