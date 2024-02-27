#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

// Define matrix dimensions
#define WIDTH 100
#define HEIGHT 100
// Define precision for floating-point comparison
#define PRECISION 0.00001

// Function Prototypes
int verify_collapse_clause();

int main() {
    int fail = verify_collapse_clause();
    if (fail) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    return fail;
}

int verify_collapse_clause() {
    int errors = 0;

    double A[HEIGHT][WIDTH];
    double B[HEIGHT][WIDTH];

    // Initialize matrix A with some values and B with zeros
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            A[i][j] = sin(i) * cos(j);
            B[i][j] = 0.0;
        }
    }

    // Using OpenACC parallel loop with collapse clause
    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            B[i][j] = A[i][j];
        }
    }

    // Verify the correctness of the operations
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (fabs(B[i][j] - A[i][j]) > PRECISION) {
                errors++;
            }
        }
    }

    return errors;
}