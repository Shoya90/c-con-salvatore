#include <stdio.h>

void incr(int *p) {
    *p = *p + 1; // p[0] = p[0] + 1
}

int main(void) {
    int x = 5;
    int y = 8;

    char str[] = "AABBCCDDEEFF";
    
    char *p = str;

    int *ip = &x;
    int **iip = &ip;

    printf("ip %p, *ip %d, iip %p, *iip %p, **iip %d\n", ip, *ip, iip, *iip, **iip);

    printf("p is %p and value of p is %c\n", p, *(p+3));

    while (*p != 0) {
        putchar(*p);
        p++;
    }

    printf("\n");

    printf("x is %d", x);
    incr(&x);
    incr(&x);
    incr(&x);
    printf("x now is %d", x);



}
