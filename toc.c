#include <stdio.h>

double factorial(double n, void* start_addr) {
    int local_var;
    printf("Standard n=%f | Stack Depth: %ld bytes\n", n, (long)start_addr - (long)&local_var);

    if(n == 0) return 1;
    return n * factorial(n-1, start_addr);
}

double factorial_tco(double n, double acc, void* start_addr) {
    //int local_var;
    //printf("TCO n=%f | Stack Depth: %ld bytes\n", n, (long)start_addr - (long)&local_var);

   if (n == 0) return acc;
    return factorial_tco(n-1, n * acc, start_addr);
}

int main(void) {
    int root;

    double n = 12;

	printf("--- Standard Factorial ---\n");
    factorial(n, &root);

	printf("\n--- TCO Factorial ---\n");
	factorial_tco(n, 1, &root);
}
