/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
void tran_three_two_v0(int A[32][32], int B[32][32]) { // 287
    int i, j, k;
    int a0, a1, a2,a3,a4,a5,a6,a7;
    for (i = 0;i < 32; i+=8) {
        for (j = 0; j < 32; j += 8) {
            for (k = 0; k < 8; ++k) {
                a0 = A[i+k][j+0]; a1 = A[i+k][j+1]; a2 = A[i+k][j+2]; a3 = A[i+k][j+3];
                a4 = A[i+k][j+4]; a5 = A[i+k][j+5]; a6 = A[i+k][j+6]; a7 = A[i+k][j+7];
                B[j+0][i+k] = a0; B[j+1][i+k] = a1; B[j+2][i+k] = a2; B[j+3][i+k] = a3;
                B[j+4][i+k] = a4; B[j+5][i+k] = a5; B[j+6][i+k] = a6; B[j+7][i+k] = a7;
            }
        }
    }
}
void tran_three_two_v1(int A[32][32], int B[32][32]) { // 283
    int i, j, k;
    int a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0;
    for (i = 0; i < 32; i+= 8) {  // A(i,j)块复制到B(j, i)块
        for (j = 0; j < 32; j+=8) {
            if (i == j) {  // 原地复制这个8*8的块
                for (k = 0; k < 8; ++k) {  // 第k行
                    a0 = A[i+k][j+0];
                    a1 = A[i+k][j+1];
                    a2 = A[i+k][j+2];
                    a3 = A[i+k][j+3];
                    a4 = A[i+k][j+4];
                    a5 = A[i+k][j+5];
                    a6 = A[i+k][j+6];
                    a7 = A[i+k][j+7];
                    B[i+k][j+0] = a0;
                    B[i+k][j+1] = a1;
                    B[i+k][j+2] = a2;
                    B[i+k][j+3] = a3;
                    B[i+k][j+4] = a4;
                    B[i+k][j+5] = a5;
                    B[i+k][j+6] = a6;
                    B[i+k][j+7] = a7;
                }
            }
            else {
               for (k = 0; k < 8; ++k) {  // 第k行
                    B[j+0][i+k] = A[i+k][j+0];
                    B[j+1][i+k] = A[i+k][j+1];
                    B[j+2][i+k] = A[i+k][j+2];
                    B[j+3][i+k] = A[i+k][j+3];
                    B[j+4][i+k] = A[i+k][j+4];
                    B[j+5][i+k] = A[i+k][j+5];
                    B[j+6][i+k] = A[i+k][j+6];
                    B[j+7][i+k] = A[i+k][j+7];
                } 
            }
        }
    }
    for (i = 0; i < 32; i += 8) {
        for (k = 0; k < 8; ++k) {
            for (j = i+k+1; j < i+8; ++j) {
                a0 = B[i+k][j];
                B[i+k][j] = B[j][i+k];
                B[j][i+k] = a0;
            }
        }
    }
}

void tran_six_four_v1(int A[64][64], int B[64][64]) {  // 1307
   int i, j, k, tmp;  //4
    int a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0;  //8
    for (i = 0; i < 64; i+= 8) {  // A(i,j)块复制到B(j, i)块
        for (j = 0; j < 64; j+=8) {
            if (i == j) {// 原地复制这个8*8的块 ------>对角线的8*8矩阵，先复制再进行块内转换 有30个miss
                for (k = 0; k < 8; ++k) {  // 第k行 16个miss
                    a0 = A[i+k][j+0];
                    a1 = A[i+k][j+1];
                    a2 = A[i+k][j+2];
                    a3 = A[i+k][j+3];
                    a4 = A[i+k][j+4];
                    a5 = A[i+k][j+5];
                    a6 = A[i+k][j+6];
                    a7 = A[i+k][j+7];
                    B[i+k][j+0] = a0;
                    B[i+k][j+1] = a1;
                    B[i+k][j+2] = a2;
                    B[i+k][j+3] = a3;
                    B[i+k][j+4] = a4;
                    B[i+k][j+5] = a5;
                    B[i+k][j+6] = a6;
                    B[i+k][j+7] = a7;
                }
            }
            else {  
               for (k = 0; k < 8; ++k) {  // 第k行
                    B[j+0][i+k] = A[i+k][j+0];
                    B[j+1][i+k] = A[i+k][j+1];
                    B[j+2][i+k] = A[i+k][j+2];
                    B[j+3][i+k] = A[i+k][j+3];
                    if (k == 3) {
                        a0 = A[i+k][j+4];
                        a1 = A[i+k][j+5];
                        a2 = A[i+k][j+6];
                        a3 = A[i+k][j+7];
                    }
                    if (k == 4) {
                        a4 = A[i+k][j+4];
                        a5 = A[i+k][j+5];
                        a6 = A[i+k][j+6];
                        a7 = A[i+k][j+7];
                    }
                }
                for (k = 7; k >= 0; --k) {  // 第k行
                    if (k == 4) {
                        B[j+4][i+k] = a4;
                        B[j+5][i+k] = a5;
                        B[j+6][i+k] = a6;
                        B[j+7][i+k] = a7;
                        continue;
                    }
                    if (k == 3) {
                        B[j+4][i+k] = a0;
                        B[j+5][i+k] = a1;
                        B[j+6][i+k] = a2;
                        B[j+7][i+k] = a3;
                        continue; 
                    }
                    B[j+4][i+k] = A[i+k][j+4];
                    B[j+5][i+k] = A[i+k][j+5];
                    B[j+6][i+k] = A[i+k][j+6];
                    B[j+7][i+k] = A[i+k][j+7];
                }  
            }
        }
    }
    for (i = 0; i < 64; i += 8) {
        for (k = 0; k < 4; ++k) { // 0-4行内转换
            for (j = k+1; j < 4; ++j) {  // (r+k, r+j)
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j][i+k];
                B[i+j][i+k] = tmp;
            }
            for (j = k+4+1; j < 8; ++j) {
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j-4][i+k+4];
                B[i+j-4][i+k+4] = tmp; 
            }
        }
        k = 2;
        a0 = B[i+k][i+4];
        a1 = B[i+k][i+5];
        a2 = B[i+k][i+6];
        a3 = B[i+k][i+7];
        k = 3;
        a4 = B[i+k][i+4];
        a5 = B[i+k][i+5];
        a6 = B[i+k][i+6];
        a7 = B[i+k][i+7]; 
        // 记住 第2行和第三行后四个元素
        for (k = 4; k < 8; ++k) {
            for (j = k-3; j < 4; ++j) {  // (i+k, i+j)
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j+4][i+k-4];
                B[i+j+4][i+k-4] = tmp; 
            }
            for (j = k+1; j < 8; ++j) {
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j][i+k];
                B[i+j][i+k] = tmp;
            }  
        }
       /* for (k = 7; k >= 4; --k) { // 左下4*4和右上4*4交换
            a0 = B[i+k][i+0];
            a1 = B[i+k][i+1];
            a2 = B[i+k][i+2];
            a3 = B[i+k][i+3];
            a4 = B[i+k-4][i+4];
            a5 = B[i+k-4][i+5];
            a6 = B[i+k-4][i+6];
            a7 = B[i+k-4][i+7]; 

            B[i+k-4][i+4] = a0;
            B[i+k-4][i+5] = a1; 
            B[i+k-4][i+6] = a2;
            B[i+k-4][i+7] = a3;
            B[i+k][i+0] = a4;
            B[i+k][i+1] = a5;
            B[i+k][i+2] = a6;
            B[i+k][i+3] = a7; 
        }*/
        // k = 7
        tmp = B[i+7][i+0];
        B[i+7][i+0] = a4;
        a4 = tmp;

        tmp = B[i+7][i+1];
        B[i+7][i+1] = a5;
        a5 = tmp;

        tmp = B[i+7][i+2];
        B[i+7][i+2] = a6;
        a6 = tmp; 

        tmp = B[i+7][i+3];
        B[i+7][i+3] = a7;
        a7 = tmp;

        B[i+3][i+4] = a4; 
        B[i+3][i+5] = a5;
        B[i+3][i+6] = a6;
        B[i+3][i+7] = a7;
        // k = 6
        tmp = B[i+6][i+0];
        B[i+6][i+0] = a0;
        a0 = tmp;

        tmp = B[i+6][i+1];
        B[i+6][i+1] = a1;
        a1 = tmp;

        tmp = B[i+6][i+2];
        B[i+6][i+2] = a2;
        a2 = tmp; 

        tmp = B[i+6][i+3];
        B[i+6][i+3] = a3;
        a3 = tmp;
        B[i+2][i+4] = a0; 
        B[i+2][i+5] = a1;
        B[i+2][i+6] = a2;
        B[i+2][i+7] = a3;

        for (k = 5; k >= 4; --k) { 
            a0 = B[i+k][i+0];
            a1 = B[i+k][i+1];
            a2 = B[i+k][i+2];
            a3 = B[i+k][i+3];
            a4 = B[i+k-4][i+4];
            a5 = B[i+k-4][i+5];
            a6 = B[i+k-4][i+6];
            a7 = B[i+k-4][i+7]; 

            B[i+k-4][i+4] = a0;
            B[i+k-4][i+5] = a1; 
            B[i+k-4][i+6] = a2;
            B[i+k-4][i+7] = a3;
            B[i+k][i+0] = a4;
            B[i+k][i+1] = a5;
            B[i+k][i+2] = a6;
            B[i+k][i+3] = a7; 
        }
    } 
}

void tran_six_four_v2(int A[64][64], int B[64][64]) {  // 1251 
    // 30*8+18*56 = 1248
    int i, j, k, tmp;  //4
    int a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0;  //8
    for (i = 0; i < 64; i+=8) {  // A(i,j)块复制到B(j, i)块
        for (j = 0; j < 64; j+=8) {
            if (i == j) {  // 原地复制这个8*8的块
                for (k = 0; k < 8; ++k) {  // 对角线上方块有 16个miss + 14
                    a0 = A[i+k][j+0];
                    a1 = A[i+k][j+1];
                    a2 = A[i+k][j+2];
                    a3 = A[i+k][j+3];
                    a4 = A[i+k][j+4];
                    a5 = A[i+k][j+5];
                    a6 = A[i+k][j+6];
                    a7 = A[i+k][j+7];
                    B[i+k][j+0] = a0;
                    B[i+k][j+1] = a1;
                    B[i+k][j+2] = a2;
                    B[i+k][j+3] = a3;
                    B[i+k][j+4] = a4;
                    B[i+k][j+5] = a5;
                    B[i+k][j+6] = a6;
                    B[i+k][j+7] = a7;
                }
            }
            else {  // (i,j)  第k行 对于一个非对角线上方块，产生18个miss
               for (k = 0; k < 8; ++k) {  // A方块中8行的前四个元素，放进B方块的前四行中
                    B[j+0][i+k] = A[i+k][j+0]; //有12个miss
                    B[j+1][i+k] = A[i+k][j+1];
                    B[j+2][i+k] = A[i+k][j+2];
                    B[j+3][i+k] = A[i+k][j+3];
                    if (k == 2) {
                        a0 = A[i+k][j+4];
                        a1 = A[i+k][j+5];
                        a2 = A[i+k][j+6];
                        a3 = A[i+k][j+7];
                    }
                    if (k == 3) {
                        a4 = A[i+k][j+4];
                        a5 = A[i+k][j+5];
                        a6 = A[i+k][j+6];
                        a7 = A[i+k][j+7];
                    } // 记住第三行和第二行 后四个元素
                }
                // cache已经有A方块中第4~7行元素，
                // 访问B方块中第4-8行产生4个miss，访问A方块中第0-1行获取后四个元素有2个miss
                for (k = 7; k >= 0; --k) {  // 第k行
                    if (k == 3) {// 第三行和第二行元素直接赋值，不用调入cache而产生miss eviction
                        B[j+4][i+k] = a4;
                        B[j+5][i+k] = a5;
                        B[j+6][i+k] = a6;
                        B[j+7][i+k] = a7;
                        continue;
                    }
                    if (k == 2) {
                        B[j+4][i+k] = a0;
                        B[j+5][i+k] = a1;
                        B[j+6][i+k] = a2;
                        B[j+7][i+k] = a3;
                        continue; 
                    }
                    B[j+4][i+k] = A[i+k][j+4];
                    B[j+5][i+k] = A[i+k][j+5];
                    B[j+6][i+k] = A[i+k][j+6];
                    B[j+7][i+k] = A[i+k][j+7];
                }  
            }
        }
    }

    //对角线上矩阵有14个miss
    for (i = 0; i < 64; i += 8) {
        for (k = 0; k < 4; ++k) { // 0-4行内转换, 两个4*4矩阵内转换  4次miss
            for (j = k+1; j < 4; ++j) {  // (r+k, r+j)
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j][i+k];
                B[i+j][i+k] = tmp;
            }
            for (j = k+4+1; j < 8; ++j) {
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j-4][i+k+4];
                B[i+j-4][i+k+4] = tmp; 
            }
        }
        k = 2;
        a0 = B[i+k][i+4];
        a1 = B[i+k][i+5];
        a2 = B[i+k][i+6];
        a3 = B[i+k][i+7];
        k = 3;
        a4 = B[i+k][i+4];
        a5 = B[i+k][i+5];
        a6 = B[i+k][i+6];
        a7 = B[i+k][i+7]; 
        // 记住 第2行和第三行后四个元素
        for (k = 4; k < 8; ++k) { // 4-7行内转换, 两个4*4矩阵内转换  4次miss
            for (j = k-3; j < 4; ++j) {  // (i+k, i+j)
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j+4][i+k-4];
                B[i+j+4][i+k-4] = tmp; 
            }
            for (j = k+1; j < 8; ++j) {
                tmp = B[i+k][i+j];
                B[i+k][i+j] = B[i+j][i+k];
                B[i+j][i+k] = tmp;
            }  
        }
    // 将之前记录的第二行还有第三行后四个元素和第六行第七行前四个元素交换
    // 第六行第七行已经在cache中了，不会有miss，存储第2行和第3行元素有2个miss
        // k = 7 
        tmp = B[i+7][i+0];
        B[i+7][i+0] = a4;
        a4 = tmp;

        tmp = B[i+7][i+1];
        B[i+7][i+1] = a5;
        a5 = tmp;

        tmp = B[i+7][i+2];
        B[i+7][i+2] = a6;
        a6 = tmp; 

        tmp = B[i+7][i+3];
        B[i+7][i+3] = a7;
        a7 = tmp;

        B[i+3][i+4] = a4; 
        B[i+3][i+5] = a5;
        B[i+3][i+6] = a6;
        B[i+3][i+7] = a7;
        // k = 6
        tmp = B[i+6][i+0];
        B[i+6][i+0] = a0;
        a0 = tmp;

        tmp = B[i+6][i+1];
        B[i+6][i+1] = a1;
        a1 = tmp;

        tmp = B[i+6][i+2];
        B[i+6][i+2] = a2;
        a2 = tmp; 

        tmp = B[i+6][i+3];
        B[i+6][i+3] = a3;
        a3 = tmp;
        B[i+2][i+4] = a0; 
        B[i+2][i+5] = a1;
        B[i+2][i+6] = a2;
        B[i+2][i+7] = a3;

        for (k = 5; k >= 4; --k) {  // 4个miss
            a0 = B[i+k][i+0];
            a1 = B[i+k][i+1];
            a2 = B[i+k][i+2];
            a3 = B[i+k][i+3];
            a4 = B[i+k-4][i+4];
            a5 = B[i+k-4][i+5];
            a6 = B[i+k-4][i+6];
            a7 = B[i+k-4][i+7]; 

            B[i+k-4][i+4] = a0;
            B[i+k-4][i+5] = a1; 
            B[i+k-4][i+6] = a2;
            B[i+k-4][i+7] = a3;
            B[i+k][i+0] = a4;
            B[i+k][i+1] = a5;
            B[i+k][i+2] = a6;
            B[i+k][i+3] = a7; 
        }
    } 
}

void tran(int A[67][61], int B[61][67]) {
    int i, j, r, c;
    int bsize = 18; 
    // bsize = 8, miss = 2118; 
    // bsize = 16, miss = 1992
    // bsize = 18, miss = 1961
    for (i = 0; i<67; i+= bsize) {
        for (j = 0; j<61; j+= bsize) { // 
            for (r = i; r < i + bsize && r < 67; ++r) {
                for (c = j; c < j + bsize && c < 61; ++c) 
                    B[c][r] = A[r][c]; 
            }
        }
    }
}
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32) {
        tran_three_two_v1(A, B);
    }
    else if (M == 64 && N == 64) {
        tran_six_four_v2(A,B);
    }
    else if (M == 61 && N == 67) {
        tran(A, B); 
    }
    return ;   
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}
char desc[] = "Simple row-wise scan of B transpose";
void row_trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;
    for (i = 0; i <N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[j][i];
            B[i][j] = tmp;
        }
    }
}
/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 

    //registerTransFunction(row_trans, desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

