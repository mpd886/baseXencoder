#include <stdio.h>
#include <assert.h>
#include "baseX.h"

void base64_encodeNoPadding() {
    const char* result = encode("thi"); 
    const char* expected = "dGhp";

    assert(strcmp(result, expected) == 0);
}

void base64_moreBytes() {
    const char* expected = "dGhpc2lz";
    const char* result = encode("thisis");
    assert(strcmp(result, expected) == 0);
}


typedef void (*test_func)();

int main() {
    int i;
    test_func tests[] = {
        base64_encodeNoPadding,
        base64_moreBytes
    };

    const int total_tests = sizeof(tests)/sizeof(tests[0]);

    for (i = 0 ; i <  total_tests ; ++i)  {
        tests[i]();
    }

    printf("%d tests passed\n", total_tests);
}

