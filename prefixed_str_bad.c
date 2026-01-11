#include <stdio.h>

void ps_init(char *buf, char *str, int len) {
    *buf = (char)len;

    for (int i = 0; i < len; i++) {
        buf[i+1] = str[i];
    }
}

void ps_print(char *str) {
    unsigned char len = *str;
    for (int i = 0; i < len; i++) {
        putchar(str[i+1]);
    }
}

int main(void) {
    char buf[256];
    ps_init(buf, "Hello\000 World", 12);
    
    ps_print(buf);

    return 0;
}
