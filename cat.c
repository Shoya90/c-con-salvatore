#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line {
    char *s;
    struct line *next;
    struct line *prev;
};


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Invalid command argument\n");
        return 1;
    }


    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File does not exist\n");
        return 1;
    }

    char *order = argv[2];

    char buf[1024];
    struct line *head = NULL;
    struct line *tail = NULL;

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        // create a new struct for each line
        struct line *l = malloc(sizeof(struct line));
        size_t len = strlen(buf);
        
        // create new space for s, since we reuse buf and can't assign it to l->s
        l->s = malloc(len + 1);
        
        // copy bytes of the line read into buf, to l->s
        for(size_t i = 0; i <= len; i++) {
            l->s[i] = buf[i];
        }

        l->prev = head;
        head = l;

        if (l->prev != NULL) {
            l->prev->next = l;
        } else {
            l->next = NULL;
            tail = l;
        }
        
    }

    fclose(fp);
   
    if (*order == 'r') {
        while (head) {
            printf("%s", head->s);
            head = head->prev;
        }
    } else {
         while (tail) {
            printf("%s", tail->s);
            tail = tail->next;
         }    
    }



    return 0;
}
