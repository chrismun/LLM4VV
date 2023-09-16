#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1024

// Function to initialize an array with random values
void init_array(float* a, int size) {
    for(int i=0; i<size; ++i) {
        a[i] = (float)rand() / RAND_MAX;
    }
}

// Function to perform vector addition using OpenACC
void vec_add(float* a, float* b, float* c, int size) {
    #pragma acc kernels
    for(int i=0; i<size; ++i) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    float* a = (float*) malloc(SIZE * sizeof(float));
    float* b = (float*) malloc(SIZE * sizeof(float));
    float* c = (float*) malloc(SIZE * sizeof(float));

    // Initialize the arrays
    init_array(a, SIZE);
    init_array(b, SIZE);

    // Vector addition using OpenACC
    vec_add(a, b, c, SIZE);

    // Test the result
    int correct = 1;
    for(int i=0; i<SIZE; i++) {
        if(c[i] != a[i]+b[i]) {
            correct = 0;
            break;
        }
    }

    // Clean up
    free(a); free(b); free(c);

    // Test Result
    if(correct) {
        printf("Test passed.\n");
        return 0;
    } else {
        printf("Test failed.\n");
        return 1;
    }
}