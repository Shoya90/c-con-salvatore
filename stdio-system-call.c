#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

#define CHARS_PER_LINE 16
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
            
            printf("\t|");
            for (size_t j=printed_offset; j <= i; j++) {
                int c = isprint(byte[j]) ? byte[j] : '.';
                printf("%c", c);
            }
            printf("|\n");
            printed_offset = i + 1;
        }
    }
}


int main(void) {
    int fd = open("stdio-system-call.c", O_RDONLY);
    if (fd == -1) {
        perror("Unable to open file");
        return 1;
    }

    char buf[32];
    ssize_t n_read;

    while (1) {
        n_read = read(fd, buf, sizeof(buf));
        if (n_read == -1) {
            perror("Error reading file");
            return 1;
        }    
        if (n_read == 0) break;
        hexdump(buf, n_read);
    }

    close(fd);
    close(fd);
    return 0;
}
