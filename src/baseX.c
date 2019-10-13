#include <stdlib.h>
#include <string.h>
#include "baseX.h"


static const char base64_alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                                        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
                                        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
                                        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 
                                        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                                        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
                                        'w', 'x', 'y', 'z', '0', '1', '2', '3', 
                                        '4', '5', '6', '7', '8', '9', '+', '/' };
                                        

/*
 *  dest has 4 bytes for encoding
 *  src will have between 1 and 3 bytes
 */
void encode_block(char* dest, const char* src) {
    int i = 0;
    char clear[3] = {0};
    char *ptr = clear;
    strncpy(clear, src, 3);

    dest[i++] = base64_alphabet[(*ptr & 0xf6) >> 2];

    char c = (*ptr & 0x03) << 4;
    ptr++;
    c |= (*ptr & 0xf0) >> 4;
    dest[i++] = base64_alphabet[c];

    if (strlen(src) == 1) {
        dest[i++] = '=';
        dest[i++] = '=';
        return;
    }

    c = (*ptr & 0x0f) << 2;
    ++ptr;
    c |= (*ptr & 0xc0) >> 6;
    dest[i++] = base64_alphabet[c];

    dest[i++] = *ptr ? base64_alphabet[*ptr & 0x3f] : '=';
    ++ptr;
}


const char* encode(const char* src) {
    int blocks = strlen(src)/3 + 
                 (strlen(src)%3 ? 1 : 0); 
    char* encoded = (char*)calloc(blocks, 4);
    char* encoded_ptr = encoded;
    int i = 0;

    while (i++ < blocks) {
        encode_block(encoded_ptr, src);
        src += 3;
        encoded_ptr += 4;
    }

    return encoded;
}

