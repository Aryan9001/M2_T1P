#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M_MATRIX 90

void randomMatrix(int N, int m[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = rand() % 10; // Generate random values between 0 and 9
        }
    }
}

void mMatrix(int N, int A[N][N], int B[N][N], int C[N][N]) {
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

void ToFile(int N, int matrix[N][N], const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%d ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int N = rand() % MAX_SIZE_MATRIX + 1; // Random matrix size between 1 and MAX_SIZE_MATRIX

    int A[MAX_SIZE_MATRIX][MAX_SIZE_MATRIX], B[MAX_SIZE_MATRIX][MAX_SIZE_MATRIX], C[MAX_SIZE_MATRIX][MAX_SIZE_MATRIX];

    // Generate random matrices A and B
    randomMatrix(N, A);
    randomMatrix(N, B);

    clock_t start_time = clock();

    // Multiply matrices A and B
    mMatrix(N, A, B, C);

    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / (CLOCKS_PER_SEC / 1000000); // Convert to microseconds

    // Print matrix C
    printf("Resultant Matrix C:\n");
    pMatrix(N, C);

    // Write matrix C to a file
    ToFile(N, C, "result.txt");

    printf("Execution time: %.6f microseconds\n", execution_time);

    return 0;
}
