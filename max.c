#include <stdio.h>
#include <limits.h>

int find_max_linear(int arr[]) {
    int i = 0;
    int max = INT_MIN;
    while(i*4 < (int)sizeof(arr)) {
        if (arr[i] > max) max = arr[i];
        i++
    }

    return max;
}

int main(void) {
    int arr[] = {2, 5, 1, 3, 0};
    int max = find_max_linear(arr);

    printf("max is %d", max);
}
