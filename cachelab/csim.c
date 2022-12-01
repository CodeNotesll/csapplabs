#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
void option_showcase(const char* s) {
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", s);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\n");
    printf("Examples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", s);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", s);
}
int main(int argc, char* argv[])
{
    if (argc == 1) {
        option_showcase(argv[0]);
        exit(EXIT_FAILURE);
    }
    int ch; 
    int s;  //  Number of set index bits ==> 2^s is the number of sets
    int e;  //  Number of lines per set  
    int b;  //  Number of block offset bits. ==> 2^b is size of cache block
    char* file;   // trace file
    int verbal = 0;
    
    while((ch = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (ch)
        {
        case 'h':
            option_showcase(argv[0]);
            break;
        case 'v': 
            verbal = 1;
            break;
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            e = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            file = optarg;
            break;
        default:
            option_showcase(argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (!s || !e || !b) {
        printf("Error: arguments should be positive\n");
        exit(EXIT_FAILURE);
    }
    printf("%d, %d, %d,%d, %s\n", s,e,b,verbal,file);
    int hit_num = 0, miss_num = 0, eviction_num = 0;
    printSummary(hit_num, miss_num, eviction_num);
    return 0;
}
