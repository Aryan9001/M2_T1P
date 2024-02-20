#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define M_Matrix 90

void randomMatrix(int N, int m[N][N]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = rand() % 10; // Generate random values between 0 and 9
        }
    }
}

void mMatrix(int N, int A[N][N], int B[N][N], int C[N][N]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void pMatrix(int N, int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void ToFile(int N, int mat[N][N], const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%d ", mat[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int N = rand() % M_Matrix + 1; // Random matrix size between 1 and 90

    printf("Matrix Size: %d x %d\n", N, N); 

    int A[N][N], B[N][N], C[N][N];

    // Generate random matrices A and B
    randomMatrix(N, A);
    randomMatrix(N, B);

    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

    // Multiply matrices A and B
    mMatrix(N, A, B, C);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) * 1e6 + (end_time.tv_nsec - start_time.tv_nsec) / 1e3;

    // Print matrix C
    printf("Resultant Matrix C:\n");
    pMatrix(N, C);

    // Write matrix C to a file
    ToFile(N, C, "result.txt");

    printf("Execution time: %.6f microseconds\n", execution_time);

    return 0;
}
