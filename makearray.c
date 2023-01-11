#include<stdio.h>
#include<stdlib.h>

int main() {
    int A[2][3];

    int **B = (int**)malloc(2*sizeof(int*));

    for (int i = 0; i < 2; ++i) {
        B[i] = (int*)malloc(3*sizeof(int));
    }
    B[0][1] = 5;
    printf("%d\n", B[0][1]);
    printf("val of A is %p\n", A); // 0x7ffe1fcbefd0
    printf("val of A+1 is %p\n", A+1); // 0x7ffe1fcbefdc  3*4 
    printf("*************\n");
    printf("val of B is %p\n", B);  //0x56469cfdb2a0
    printf("val of B+1 is %p\n", B+1); // 0x56469cfdb2a8
    printf("*************\n");
    printf("sizeof pointer is %ld\n", sizeof(int*));  // 8
    return 0;
}