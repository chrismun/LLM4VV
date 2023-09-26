#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SIZE 1024

int main() {
    int i, err = 0;
    float a[SIZE];
    float b[SIZE];
    float c[SIZE];
    float d[SIZE];

    // Initialize arrays a and b with random numbers
    for (i = 0; i < SIZE; i++) {
        a[i] = (float)rand()/(float)(RAND_MAX);
        b[i] = (float)rand()/(float)(RAND_MAX);
    }

    // Specify vector_length(256) to use 256 threads per vector
    #pragma acc parallel loop vector_length(256) copyin(a, b) copyout(c)
    for (i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    // Validate results on the CPU
    for (i = 0; i < SIZE; i++) {
        d[i] = a[i] + b[i];
    }

    // Compare CPU and GPU results
    for (i = 0; i < SIZE; i++) {
        if (abs(c[i] - d[i]) > 1e-5) {
            err++;
        }
    }

    if (err > 0) {
        printf("Test failed!\n");
    } else {
        printf("Test passed!\n");
    }

    return err;
}