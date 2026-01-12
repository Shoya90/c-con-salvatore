#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct ps {
    long len;
    char str[20]; // make str to start at the end of the struct
    // char *str     now str will point to an arbitrary adddress 
    // in memory and won't be on the continuation of where the struct is
    // that mean to access it we need an extra CPU jump
};

#define CHARS_PER_LINE 8

void hexdump(void *p, size_t len) {
    unsigned char *byte = p;
    size_t printed_offset = 0;
    for (size_t i=0; i < len; i++) {
        if (i % CHARS_PER_LINE == 0) {\
            printf("%p \t", &byte[i]);
        }
        printf("%02X ", byte[i]);
        if ((i+1) % CHARS_PER_LINE == 0 || i == len-1) {
            if (i == len -1) {
                int spaces = CHARS_PER_LINE - (len % CHARS_PER_LINE);
                spaces %= CHARS_PER_LINE;
                for (int k=0; k < spaces; k++) {
                    printf("~~ ");
                }                
            }
            
            printf("\t");
            for (size_t j=printed_offset; j <= i; j++) {
                int c = isprint(byte[j]) ? byte[j] : '.';
                printf("%c", c);
            }
            printf("\n");
            printed_offset = i + 1;
        }
    }
}

int main(void) {
    struct ps s;

    s.len = 10;

    memcpy(s.str, "Hello Joe!", 11);
    hexdump(&s, sizeof(s) - 3);

   return 0; 
}


