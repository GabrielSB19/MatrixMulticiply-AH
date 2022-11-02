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

void PrintMat(int n, float* M) {
    int i, j;

    for (j = 0; j < n; j++) {
        //printf("; \n");
        for (i = 0; i < n; i++)
            printf("%.3f ", M[i + j * n]);
        printf("; \n");
    }
    printf("\n\n");
}

int main(int argc, char** argv) {
    int nmax = 4274, i, n;  //100	134	179	239	319	426	569	759	1013 1351 1802 2403

    void (*orderings[])(int, float*, float*, float*) = { &mMatrix1,&mMatrix2,&mMatrix3,&mMatrix4,&mMatrix5,&mMatrix6 };
    const char* names[] = { "1-ijk","2-ikj","3-jik","4-jki","5-kij","6-kji" };


    float* A = (float*)malloc(nmax * nmax * sizeof(float));
    float* B = (float*)malloc(nmax * nmax * sizeof(float));
    float* C = (float*)malloc(nmax * nmax * sizeof(float));

    //struct timeval start, end;

    if (argv[1]) {
        printf("Running Part B...\n\n");

        /* fill matrices with random numbers */
        for (i = 0; i < nmax * nmax; i++) A[i] = (float)rand() / 1000;
        for (i = 0; i < nmax * nmax; i++) B[i] = (float)rand() / 1000;
        for (i = 0; i < nmax * nmax; i++) C[i] = (float)0.0;

        for (i = 0; i < 6; i++) {
            /* multiply matrices and measure the time */
            // Start measuring time
            clock_t start = clock();
            (*orderings[i])(nmax, A, B, C);
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            /* convert time to Gflop/s */
            double Gflops = 2e-9 * nmax * nmax * nmax / seconds;
            printf("%s\tn = %d;  %3.5f s ; %.4f Gflop/s\n", names[i], nmax, seconds, Gflops);

        }
    }
    else {
        printf("Running Part A...\n\n");
        printf("version    n    time(s)  Gflop/s  Normalized(ns)\n");

        for (n = 319; n <= nmax; n = n<nmax && n + 1 + n / 3>nmax ? nmax : n + 1 + n / 3) {
            /* fill matrices with random numbers */
            for (i = 0; i < n * n; i++) A[i] = (float)rand() / 1000;// (float)rand();
            for (i = 0; i < n * n; i++) B[i] = (float)rand() / 1000;// (float)rand();
            for (i = 0; i < n * n; i++) C[i] = 0;// (float)rand();

            /* multiply matrices and measure the time */
            // Start measuring time
            int MatX = 6;              // label version 1, 2, 3, 4, 5 or 6
            clock_t start = clock();
            mMatrix6(n, A, B, C);     //select multMat1, multMat2, multMat3, multMat4, multMat5 or multMat6
            // Stop measuring time and calculate the elapsed time
            clock_t end = clock();

            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            double N = n;
            double timeNormalized = (seconds * 1.0e9) / (N * N * N); //ns
            /* convert time to Gflop/s */
            double Gflops = 2e-9 * N * N * N / seconds;
            //"ijk","ikj","jik","jki","kij","kji" 
            printf("%s\t   %05d  %2.4f   %1.4f   %2.4f \n", names[MatX - 1], n, seconds, Gflops, timeNormalized);
        }
    }

    free(A);
    free(B);
    free(C);

    printf("\n\n");

    return 0;
}