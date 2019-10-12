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
    char* letters = (char*)calloc(length+1, 1);
    int i = 0;
    while (i < length) {
        letters[i++] = alphabet[(*src & 0xf6) >> 2];

        char c = (*src & 0x03) << 4;
        src++;
        c |= (*src & 0xf0) >> 4;
        letters[i++] = alphabet[c];


        c = (*src & 0x0f) << 2;
        ++src;
        c |= (*src & 0xc0) >> 6;
        letters[i++] = alphabet[c];

        letters[i++] = alphabet[*src & 0x3f];
        ++src;
    }
    return letters;
}

