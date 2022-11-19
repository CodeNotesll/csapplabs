#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc, char* argv[]) {
    int ch;
    printf("initial optind: %d, opterr = %d\n", optind, opterr);

    // option set {v, h, a, b, c}
    // option 'v' and 'h' doesn't need arg
    // option 'a' and 'b' need one arg
    // arg of option 'c' depends on command line 
    int n;
    while((ch = getopt(argc, argv, "vha:b:c::")) != -1) {
        printf("optind: %d, opterr: %d\n", optind, opterr);
        switch (ch)
        {
        case 'v':
            printf("flag v \n");
            if(optarg == NULL) 
                printf("optarg is null\n");
            printf("version: 0.11\n");
            break;
        case 'h':
            printf("flag h \n");
            break; 
        case 'a':
            printf("flag a \n");
            n = atoi(optarg);
            printf("argument of option 'a' is %d\n", n);
            break;
        case 'c':
            printf("flag c \n");
            if (optarg) {
                printf("%s \n", optarg);
            }
            else 
                printf("argument of c not given\n");
        default:  /* ? */ 
            printf("default: ch is %c\n", ch);
            printf("usage: \n");
            exit(EXIT_FAILURE);
            break;
        }
    }
    return 0;
}