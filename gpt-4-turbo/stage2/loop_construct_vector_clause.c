#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

// Define a constant for the size of vectors
#define VECTOR_SIZE 1024

bool is_correct(float *a, float *b, float *result, int size) {
    for (int i = 0; i < size; ++i) {
        if(result[i] != a[i] + b[i]) {
            return false;
        }
    }
    return true;
}

int test_vector_clause() {
    float *a, *b, *result_parallel, *result_sequential;
    int err = 0;

    // Allocation of the arrays
    a = (float *)malloc(sizeof(float)*VECTOR_SIZE);
    b = (float *)malloc(sizeof(float)*VECTOR_SIZE);
    result_parallel = (float *)malloc(sizeof(float)*VECTOR_SIZE);
    result_sequential = (float *)malloc(sizeof(float)*VECTOR_SIZE);

    // Initialize arrays
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        result_parallel[i] = 0.0f;
        result_sequential[i] = 0.0f;
    }

    // Parallel vector addition using OpenACC
    #pragma acc parallel loop vector_length(128)
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        result_parallel[i] = a[i] + b[i];
    }

    // Sequential vector addition for verification
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        result_sequential[i] = a[i] + b[i];
    }

    // Verification
    if(!is_correct(a, b, result_parallel, VECTOR_SIZE)) {
        err = 1; // Error if the results don't match
    }

    // Clean up
    free(a);
    free(b);
    free(result_parallel);
    free(result_sequential);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = test_vector_clause();

    if (failed != 0){
        failcode = failcode + 1; // Adjust the failcode according to the result
    }

    return failcode;
}