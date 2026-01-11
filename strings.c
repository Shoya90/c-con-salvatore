#include <stdio.h>
void toUpper(char str[]) {
    int i = 0;
    while(i < str[i] != '\0') {
        if (str[i]>= 'a'  && str[i] <='z') {
            printf("%c -> %c\n", str[i], str[i]-32);
            str[i] = str[i] - 32;
        }
        i++;
    }
}

int main(void) {
	char str[6] = {'h', 'e', 'l', 'l', 'o', 0};
    int i = 0;
    while(str[i] != 0) {
        printf("[%d]", str[i] + 1);
        i++;
    }
    printf("\n");
	char str1[] = "hello";
	char str2[6] = "world";
    
    char up[] = "It's mostly sunny!";
    printf("size of up %d",(int)sizeof(up));
    toUpper(up);
	printf("str: %s str1: %s str2: %s upper: %s", str, str1, str2, up);
	return 0;
}


