#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M_SIZE 90
void randomMatrix(int N, int m[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = rand() % 10; // Generate random values between 0 and 9
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
        printf("Error.\n");
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
    int N = rand() % (M_SIZE - 1) + 1; // Random matrix size between 1 and M_SIZE
    int A[M_SIZE][M_SIZE], B[M_SIZE][M_SIZE], C[M_SIZE][M_SIZE];
    // Generate random matrices A and B
    randomMatrix(N, A);
    randomMatrix(N, B);
    // Multiply matrices A and B
    mMatrix(N, A, B, C);
    // Print matrix C
    printf("Resultant Matrix C:\n");
    pMatrix(N, C);
    // Write matrix C to a file
    ToFile(N, C, "result.txt");

    return 0;
}
