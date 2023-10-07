#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10000

void verify(float *a, float *b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i] * b[i]) {
            printf("Verification failed at index: %d\n", i);
            exit(-1);
        }
    }
    printf("Verification success\n");
}

int main() {
    float *a = (float*) malloc(SIZE * sizeof(float));
    float *b = (float*) malloc(SIZE * sizeof(float));
    
    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        b[i] = (float) rand() / RAND_MAX;
    }

    #pragma acc data copyin(b[0:SIZE]), copyout(a[0:SIZE])
    {
        #pragma acc parallel loop private(b)
        for (int i = 0; i < SIZE; i++) {
            a[i] = b[i] * b[i]; // Each thread needs its private copy of b for this computation
        }
    }

    // Verify the result
    verify(a, b, SIZE);

    free(a);
    free(b);

    return 0;
}