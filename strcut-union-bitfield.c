#include <stdio.h>
#include <string.h>

struct foo {
    union { // this would make the i and a start from the same address in memory
            // so writing one will also write the other. Could be useful when 
            // only either i or a exists and both at the same time won't exist.
        int i;
        unsigned char a[4];
    };
};

struct bar {
    unsigned char a:1; // this will make a a 1-bit filed so basically a boolean
    unsigned char b:1;
    unsigned char c:1;
    unsigned char d:1;
    unsigned char e:4; // e will be 4-bits.
};

int main(void) {
    struct foo f;
    f.i = 279;
    printf("f of type foo is %zu bytes\n", sizeof(f));
    printf("f.i = %d, f.a = {%d, %d, %d, %d}\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);


    struct bar b;
    b.a = 0;
    b.b = 1;
    b.c = 2; // gcc will give warnings on this because 2 is bigger than the biggest
             // number b.c can store (1 bit)
    b.d = 3;
    b.e = 279;
    printf("b of type bar is %zu bytes\n", sizeof(b));
    printf("b.a = %d, b.b = %d, b.c = %d, b.d = %d, b.e = %d\n", b.a, b.b, b.c, b.d, b.e);

    return 0;
} 
