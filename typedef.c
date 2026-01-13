#include <stdio.h>

typedef struct {
    int n;
    int d;
} fract;

typedef fract *fractptr;

int main(void) {
    fract f;
    fractptr fp = &f;
    f.n = 1;
    f.d = 3;
    printf("%d/%d stored at %p", f.n, f.d, fp);
}
