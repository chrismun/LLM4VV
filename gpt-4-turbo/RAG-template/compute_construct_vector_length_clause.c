#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>

#ifndef T1
// T1: {feature}, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    const int size = 1 << 20; // Large enough size
    float *vec = (float*)malloc(size * sizeof(float));

    // Initialize vector
    for (int i = 0; i < size; ++i) {
        vec[i] = (float)rand() / RAND_MAX;
    }

    clock_t start_no_vect = clock();
    // Compute without specifying vector_length
    #pragma acc parallel loop
    for (int i = 0; i < size; ++i) {
        vec[i] = vec[i] * vec[i];
    }
    clock_t end_no_vect = clock();

    // Reinitialize vector
    for (int i = 0; i < size; ++i) {
        vec[i] = (float)rand() / RAND_MAX;
    }

    clock_t start_vect = clock();
    // Compute with specifying vector_length
    #pragma acc parallel loop vector_length(256)
    for (int i = 0; i < size; ++i) {
        vec[i] = vec[i] * vec[i];
    }
    clock_t end_vect = clock();

    double no_vect_time = (double)(end_no_vect - start_no_vect) / CLOCKS_PER_SEC;
    double vect_time = (double)(end_vect - start_vect) / CLOCKS_PER_SEC;

    // Check if vectorized version is faster (not a rigorous check)
    if (no_vect_time <= vect_time) {
        err = 1; // Assume vectorization didn't occur or didn't improve performance
    }

    free(vec);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 1; ++x){ // Simplified loop for demonstration
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
#endif
    return failcode;
}