#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    printf("This won't be printed before the sleep"); // this is because the libc buffers
                                                      // the stdout content to avoid calling
                                                      // system calls too many times. It will
                                                      // flush the buffer when it sees a new
                                                      // line character. to force empty the 
                                                      // buffer we could use fflush(stdout) 
    sleep(1);
    
    int fd = open("mem-map.c", O_RDONLY);
    printf("File descriptor at %d", fd);

    void *mem = mmap(NULL, 100, PROT_READ, MAP_SHARED, fd, 0);
    printf("File mapped to addr: %p", mem);

    char *s = mem;
    for (int i = 0; i < 10; i++) {
        printf("s[%d] = %c\n", i, s[i]);
    }

    close(fd);
    return 0;
}
