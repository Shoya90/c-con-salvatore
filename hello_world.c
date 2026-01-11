#include <stdio.h>

int main(void) {
	char c = 1; // 8 bits
 	short s = 2; // 156 bits
    int i = 5; // 32 bits
	long l = 899;	
    printf("C is of size %lu, and size of %lu", sizeof(i), sizeof(l));
    return 0;
}