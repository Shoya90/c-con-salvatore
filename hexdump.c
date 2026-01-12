#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct ps {
    long len;
    char str[20];
};

#define CHARS_PER_LINE 16

void hexdump(void *p, size_t len) {
    unsigned char *byte = p;
    size_t printed_offset = 0;
    for (size_t i=0; i < len; i++) {
        printf("%02X ", byte[i]);
        if ((i+1) % CHARS_PER_LINE == 0 || i == len-1) {
            if (i == len -1) {
                
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


