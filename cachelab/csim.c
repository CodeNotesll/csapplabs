#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define END "\033[0m"
#define uint64 unsigned long long 
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

unsigned long long map(char c) {
    if (isdigit(c)) {
        return c-'0';
    }
    if (c >= 'a' && c <= 'z') 
        return (c-'a') + 10;
    if (c >= 'A' && c <= 'Z')
        return (c-'A') + 10;
    return 0;
}

void print(const char* line, char action, int hitflag, int emptyline, int verbal) {
    if (!verbal)
        return ;
    if (action == 'S' || action == 'L') {
        if (hitflag) {
            printf("%s %shit%s\n", line, BLUE, END);
        }
        else if (emptyline) {
            printf("%s %smiss%s\n", line, RED, END);
        }
        else {
            printf("%s %smiss %seviction%s\n", line, RED, YELLOW, END);
        }
    } else {
        if (hitflag) {
            printf("%s %shit hit%s\n", line, RED, END);
        }
        else if (emptyline) {
            printf("%s %smiss %shit%s\n", line, RED, BLUE, END);
        }
        else {
            printf("%s %smiss %seviction %shit%s\n", line, RED, YELLOW, BLUE, END);
        }
    }
    return ;
}
int main(int argc, char* argv[])
{
    int ch; 
    int s = 0;  //  Number of set index bits ==> 2^s is the number of sets
    int e = 0;  //  Number of lines per set  
    int b = 0;  //  Number of block offset bits. ==> 2^b is size of cache block
    char* file = 0;   // trace file
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
    if (s <= 0|| e <= 0 || b <= 0 || file == 0) {
        printf("Error: arguments should be positive\n");
        option_showcase(argv[0]);
        exit(EXIT_FAILURE);
    }
    uint64 setNum = 1<<s;
    uint64 setMask = setNum - 1;
    int hit_num = 0, miss_num = 0, eviction_num = 0;
    FILE* fp = fopen(file, "r");
    char line[512];
    char action;
    uint64 setindex, tag, addr;

    uint64** cache = (uint64**)malloc(setNum*sizeof(uint64*));
    for (int i = 0; i < setNum; ++i) {
        cache[i] = (uint64*)malloc(e*sizeof(uint64));
        memset(cache[i], 0, e);
    }
    while (fgets(line,512,fp)) {
        if (line[0] == 'I')
            continue;
        action = line[1];
        addr = 0; // 8 bytes
        sscanf(line+3, "%llx", &addr);
        int j = strlen(line) - 1;
        line[j] = '\0';  // prim newline character 
        //boff = addr&boffMask; 
        setindex = (addr>>b)&setMask;
        tag = addr>>(s+b);
        int hitflag = 0;
        int emptyline = e ; // emptyline: the number of empty line if 0 
        // if emptyline == 0 then should evict
        // cache[i] 数组中从第一个位置依次放入cache line，保持第一个元素是最近未使用cache line，
        // 即待替换的元素
        // 最后一个元素是最后使用元素  
        for (int i = 0; i < e; ++i) {
            uint64 flag = cache[setindex][i];
            if (flag&1 && (flag>>(s+b)) == tag) {
                hitflag = 1;
                // 将cache[i+1..e-1] 的元素往前移动移动
                int j = i;
                while (j +1 < e && cache[setindex][j+1]&1) {
                    cache[setindex][j] = cache[setindex][j+1];
                    j ++;
                }     
               // j + 1 == e || cache[setindex][j+1]&1 == 0
               cache[setindex][j] = flag; 
            } 
            if (flag&1)
                emptyline --;
        }
        if (action == 'S' || action == 'L') {
            if (hitflag) {
                hit_num ++;
            }
            else  {  // miss
                miss_num ++;
                if (emptyline) {
                    for (int i = 0; i < e; ++i) {
                        if ((cache[setindex][i]&1) == 0) {
                            cache[setindex][i] = (tag<<(s+b)) + 1;
                            break;
                        }
                    }
                } 
                else {   // emptyline == 0 
                    eviction_num ++;
                    for (int i = 0; i+1 < e; ++i)
                        cache[setindex][i] = cache[setindex][i+1];
                    cache[setindex][e-1] = (tag<<(s+b)) + 1; 
                }   
            }
        }
        else if (action == 'M') {
            if (hitflag) {
                hit_num += 2;
            }
            else {
                miss_num ++;
                if (emptyline) {
                    for (int i = 0; i < e; ++i) {
                        if ((cache[setindex][i]&1) == 0) {
                            cache[setindex][i] = (tag<<(s+b)) + 1;
                            break;
                        }
                    } 
                }
                else {
                    eviction_num ++;
                    for (int i = 0; i+1 < e; ++i)
                        cache[setindex][i] = cache[setindex][i+1];
                    cache[setindex][e-1] = (tag<<(s+b)) + 1; 
                }
                hit_num ++;
            }
        } else {
            printf("unknown instruction: %s\n", line);
            exit(EXIT_FAILURE);
        }
        print(line+1, action, hitflag, emptyline, verbal);
    }
    printSummary(hit_num, miss_num, eviction_num);
    for (int i = 0; i < setNum; ++i) {
        free(cache[i]);
    }
    free(cache);
    fclose(fp);
    return 0;
}
