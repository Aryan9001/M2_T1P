#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define M_SIZE 90
#define M_Threads (M_SIZE / 2)

int N; // Size of the matrices
int A[M_SIZE][M_SIZE], B[M_SIZE][M_SIZE], C[M_SIZE][M_SIZE];

// Struct to hold parameters for thread function
typedef struct {
    int start_row;
    int end_row;
} TaskArgs;

// Function to generate random matrix
void randomMatrix(int matrix[M_SIZE][M_SIZE]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10; // Generate random values between 0 and 9
        }
    }
}
// Function to perform matrix multiplication for a range of rows
void* mMatrix(void* arg) {
    TaskArgs* args = (TaskArgs*)arg;
    for (int i = args->start_row; i < args->end_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}
// Function to print matrix
void pMatrix(int matrix[M_SIZE][M_SIZE]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to write matrix to file
void ToFile(int matrix[M_SIZE][M_SIZE], const char *filename) {
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

    N = rand() % M_SIZE + 1; // Random matrix size between 1 and M_SIZE
    if (N > M_SIZE) // Ensure N does not exceed the maximum size
        N = M_SIZE;

    printf("Matrix Size: %d x %d\n", N, N); 

    // Generate random matrices A and B
    randomMatrix(A);
    randomMatrix(B);

    // Initialize pthread variables
    pthread_t threads[M_Threads];
    TaskArgs args[M_Threads];

    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

    // Calculate the number of rows each thread will handle
    int rows_per_thread = N / (N / 2); // Divide rows equally among threads

    // Create threads for parallel matrix multiplication
    for (int i = 0; i < M_Threads; i++) {
        args[i].start_row = i * rows_per_thread;
        args[i].end_row = (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, mMatrix, (void*)&args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < M_Threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) * 1e6 + (end_time.tv_nsec - start_time.tv_nsec) / 1e3; // Convert to microseconds

    // Print matrix C
    printf("Resultant Matrix C:\n");
    pMatrix(C);

    // Write matrix C to a file
    ToFile(C, "result.txt");

    printf("Execution time: %.6f microseconds\n", execution_time);

    return 0;
}
