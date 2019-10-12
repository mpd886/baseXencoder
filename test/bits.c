#include <stdio.h>

int main() {
    unsigned int first =  0xf6000000;
    unsigned int second = 0x03f00000;
    unsigned int third  = 0x000f6000;
    unsigned int fourth = 0x00003f00;
    unsigned int val = 0 | (0xf6 << 24);
    printf("0x%08X\n", val);
    return 0;
}
