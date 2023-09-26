#include <stdio.h>
#include <openacc.h>

#define SIZE 1024

float a[SIZE][SIZE];
float b[SIZE][SIZE];
float c[SIZE][SIZE];

int main() {
    int i, j, k;

    // Initialize matrices.
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
            c[i][j] = 0.0f;
        }
    }

    #pragma acc data copyin(a,b) copy(c)
    {
        // Compute matrix multiplication.
        #pragma acc parallel loop collapse(2) tile(32,32)
        for(i = 0; i < SIZE; i++) {
            for(j = 0; j < SIZE; j++) {
                float sum = 0.0;
                for(k = 0; k < SIZE; k++) {
                    sum += a[i][k] * b[k][j];
                }
                c[i][j] = sum;
            }
        }
    }

    // Check the result.
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            float expected = 0.0;
            for(k = 0; k < SIZE; k++) {
                expected += a[i][k] * b[k][j];
            }
            if(expected != c[i][j]) {
                printf("Error: c[%d][%d] = %f, expected %f\n", i, j, c[i][j], expected);
                return 1;
            }
        }
    }

    printf("Test passed successfully!\n");
    return 0;
}