#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <signal.h>
#include <sys/types.h>
#include <assert.h>
#define uint64 unsigned long long 
int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;
    FILE* in_fp = fopen(argv[1], "r");
    assert(in_fp);
    char outputfilename[255];
    sprintf(outputfilename, "cache%s", argv[1]);
    FILE* out_fp = fopen(outputfilename, "w");
    char buf[255];
    
    uint64 addr = 0;
    uint64 cache_num = 0;
    uint64 mask = (1<<5) - 1;
    int col = 0;
    while (fgets(buf, 255, in_fp)) {
        if ((buf[0] != 'L' && buf[0] != 'S') || buf[1] != ' ') {
            fprintf(stderr, "line%s format error\n", buf);
            exit(EXIT_FAILURE);
        }
        sscanf(buf+2, "%llx", &addr);
        cache_num = (addr>>5)&mask;
        if (col < 60)
            fprintf(out_fp, "%llu ", cache_num);
        else 
            fprintf(out_fp, "%llu\n", cache_num);
        col++;
        col%=61;
    }
}