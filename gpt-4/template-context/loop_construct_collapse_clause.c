#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#define N 1000
#define M 1000

bool test() {
    // Initialize a 2D array with random numbers
    float a[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = rand() / (float)RAND_MAX;
        }
    }
    
    // Calculate the multiplication of all elements in parallel
    float result = 1.0f;
    #pragma acc parallel loop collapse(2) reduction(*:result)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            result *= a[i][j];
        }
    }
    
    // Check the result on the CPU to see if it matches
    float expected_result = 1.0f;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            expected_result *= a[i][j];
        }
    }
    
    // Return whether the test passed
    return fabs(result - expected_result) < 0.001f;
}

int main() {
    if (test()) {
        printf("Test passed\n");
        return 0;
    } else {
        printf("Test failed\n");
        return 1;
    }
}