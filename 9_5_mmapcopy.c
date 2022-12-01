#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1)  {
       fprintf(stderr, "cannot stat file %s\n", argv[1]);
       exit(EXIT_FAILURE); 
    }

    if (!S_ISREG(st.st_mode)) {
       fprintf(stderr, "not regular file: %s\n", argv[1]);
       exit(EXIT_FAILURE);  
    }

    const char* bufp = (char*)mmap(NULL,st.st_size,PROT_READ,MAP_PRIVATE,fd,0);
    write(1, bufp, st.st_size);
    exit(EXIT_SUCCESS);
}