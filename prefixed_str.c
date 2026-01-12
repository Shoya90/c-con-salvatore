/* Create a prefixed length string in C.
 * The string in the struct is C safe and can still contain NULL terminator.
 * The ps_print function will print the string with the specified length (
 * ignoring the NULL terminator inside the string).
 * The struct keeps track of the reference counter accessing the string and
 * will free the memory allocated by malloc once no other pointer points to it.
 * */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


struct ps {
    uint32_t len;
    uint32_t ref_count;
    uint32_t guard;
    char str[];
};

char *ps_create(char *str, int len) {
    struct ps *p = malloc(sizeof(struct ps)+len+1);
    //uint32_t *lenptr = (uint32_t*) s;
    p->len = len;
    p->ref_count = 1;
    p->guard = 0xDEADBEEF;

    for (int i = 0; i < len; i++) {
        p->str[i] = str[i];
    }

    p->str[len] = 0;

    return p->str;
}

void ps_free(char *s) {
    free(s - sizeof(struct ps));
}

void ps_validate(struct ps *s) {
    if (s->guard != 0xDEADBEEF) {
        printf("INVALID STRING: Aborting\n");
        exit(1);
    }
}

void ps_release(char *s){    
    struct ps *p = (struct ps*)(s - sizeof(*p));

    ps_validate(p);

    p->ref_count--;
    if (p->ref_count == 0) {
        ps_free(s);
    }

}

void ps_retain(char *s) {
    struct ps *p = (struct ps*)(s - sizeof(*p));

    ps_validate(p);

    p->ref_count++;
}

void ps_print(char *s) {
    struct ps *p = (struct ps*)(s - sizeof(*p));
    for (int i = 0; i < p->len; i++) {
        putchar(p->str[i]);
    }

    printf("\n");
}

uint32_t ps_length(char *s) {
    struct ps *p = (struct ps*)(s - sizeof(*p));
    return p->len;
}

char *global_str;

int main(void) {
    char *mystr = ps_create("Hello World", 11);
    global_str = mystr;

    // we need to retain the ref count
    ps_retain(mystr);

    int l = (int) ps_length(mystr);
    ps_print(mystr);

    
    printf("length: %d, string: %s\n", l, mystr);
    ps_release(mystr);
    

    ps_print(global_str);

    ps_release(mystr);

    // releasing a released string should result in an exit
    ps_release(mystr);

    return 0;
}













