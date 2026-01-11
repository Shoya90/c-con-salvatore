#include <stdio.h>
#include <stdlib.h>


struct fract {
    int num;
    int den;
};

/*
 * |0000|0000|
 * 2 integers representing the numinator and denominator of a fraction.
 * */
struct fract create_fraction(int num, int den) {
    struct fract f;

    f.num = num;
    f.den = den;

    return f;
}

void simplify_fraction(struct fract *f) {
    int starter = f->num;
    if (starter > f->den) {
        starter = f->den;
    }


    for (int d = starter; d >= 2; d--) {
        if (f->num % d == 0 && f->den % d == 0) {
            f->num /= d;
            f->den /= d;
        }
    }
}

void print_fraction(struct fract *f) {
    printf("%d/%d\n", f->num, f->den);
}

int main(void) {
    struct fract f1 = create_fraction(12, 36);
    struct fract f2 = create_fraction(15, 5);


    print_fraction(&f1);
    simplify_fraction(&f1);
    print_fraction(&f1);
    
    print_fraction(&f2);
    simplify_fraction(&f2);
    print_fraction(&f2);

    return 0;
}
