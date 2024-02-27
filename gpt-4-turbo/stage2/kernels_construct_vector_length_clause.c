#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    const int vector_length = 64; // Example vector length
    const int num_elements = 1024; // Total number of elements to process
    float *a = (float*)malloc(sizeof(float) * num_elements);
    float *b = (float*)malloc(sizeof(float) * num_elements);

    // Initialize arrays
    for (int i = 0; i < num_elements; ++i) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0f;
    }

#pragma acc kernels vector_length(vector_length)
    for (int i = 0; i < num_elements; ++i) {
        b[i] = a[i] * a[i];
    }

    // Check results
    for (int i = 0; i < num_elements; ++i) {
        if (fabs(b[i] - (a[i] * a[i])) > 1e-5) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}