#include <stdio.h>
#include <stdlib.h>

/*
 * function names, like array names, are pointers
 * with function pointers, we can pass callback functions
 * to otherfunctions.
 * */

void hello(void) {
    printf("hello\n");
}

int compare_ints(const void *a, const void *b) {
    const int *ap = (int*)a;
    const int *bp = (int*)b;

    if(*ap > *bp) return 1;
    if(*ap < *bp) return -1;
    return 0; 
}

int main(void) {
    void(*hello_ptr)(void); // this is pointer type to a function with void args and void return

    hello_ptr = hello;
    int n = 3;
    while(n--) {
        hello_ptr();
    }

    int arr[25];
    for(int i = 0; i < 25; i++) {
        arr[i] = rand() & 127;
    }

    qsort(arr, 25, sizeof(int), compare_ints);

    for(int i = 0; i < 25; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
