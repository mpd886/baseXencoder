#include <stdlib.h>
#include <string.h>
#include "baseX.h"


static const char* _make_base64_alphabet() {
    char *alpha = (char*)calloc(64, 1);
    int i = 0;
    char c = 'A';

    while(c <= 'Z') alpha[i++] = c++;
    c = 'a';
    while(c <= 'z') alpha[i++] = c++;
    c = '0';
    while(c <= '9') alpha[i++] = c++;
    alpha[i++] = '+';
    alpha[i++] = '/';

    return alpha;
}

const char* encode(const char* src) {
    const char* alphabet = _make_base64_alphabet();
    int length = strlen(src) * 8 / 6;
    int padding = strlen(src)%3;
    char* clear = (char*)calloc(length+padding, 1);
    strcpy(clear, src); 
    char* encoded = (char*)calloc(length+padding+1, 1);
    int i = 0;

    while (i < length+padding) {
        encoded[i++] = alphabet[(*clear & 0xf6) >> 2];

        char c = (*clear & 0x03) << 4;
        clear++;
        c |= (*clear & 0xf0) >> 4;
        encoded[i++] = alphabet[c];


        c = (*clear & 0x0f) << 2;
        ++clear;
        c |= (*clear & 0xc0) >> 6;
        encoded[i++] = alphabet[c];

        encoded[i++] = *clear ? alphabet[*clear & 0x3f] : '=';
        ++clear;
    }

    return encoded;
}

