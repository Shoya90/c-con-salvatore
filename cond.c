#include <stdio.h>

void while_goto_counter(int to) {
    int i = 0;
    
loop:
    if (i < to) goto enter_loop;
    return;
enter_loop:
    printf("%d\n", i);
    i++;
    goto loop;
}

void count_loop(int current, int to) {
    printf("current addr: %p, to addr: %p\n", &current, &to);
    if (current > to) {
        return;
     }
    printf("%d\n", current);
    count_loop(current+1, to);
}

void count_tco(int start, int end) {
iterate:
    if (start > end) return;    
    printf("%d\n", start);
    start = start + 1;
    goto iterate;
}

int main(void) {
    // while_goto_counter(10);
    count_tco(0, 10);
    return 0;
}
