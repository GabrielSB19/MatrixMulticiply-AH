#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
#include <time.h>


//IJK
void mMatrix1(int n, float*A, float* B, float* C) {
    int i, j, k;
    float sum = 0.0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; // C[i][j] += A[i][k] * B[k][j]; (a)Version ij k
        }
}

//JIK
void mMatrix2(int n, float* A, float* B, float* C) {
    int i, j, k;
    for (j = 0; j < n; j++)
        for (i = 0; i < n; i++) {
            for (k = 0; k < n; k++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += [i][k]*B[k][j]; (b) Version jik
        }
}

//JKI
void mMatrix3(int n, float* A, float* B, float* C) {
    int i, j, k;
    for (j = 0; j < n; j++)
        for (k = 0; k < n; k++) {
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += A[i][k]*B[k][j]; (c) Version jki
        }
}

//KJI
void mMatrix4(int n, float* A, float* B, float* C) {
    int i, j, k;
    for (k = 0; k < n; k++)
        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];    //C[i][j] += A[i][k]*B[k][j];   (d) Version kji
        }
}

//KIJ
void mMatrix5(int n, float* A, float* B, float* C) {
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n];   //C[i][j] += A[i][k]*B[k][j]; (e) Version kij
        }
}

//IKJ
void mMatrix6(int n, float* A, float* B, float* C) {
    int i, j, k;
    float r;
    for (i = 0; i < n; i++)
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++)
                C[i + j * n] += A[i + k * n] * B[k + j * n]; //C[i][j] += A[i][k]*B[k][j]; // (f) Version ikj
        }
}