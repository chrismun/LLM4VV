#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void random_init(float* data, int size) {
    for (int i=0; i<size; ++i)
        data[i] = rand() / (float)RAND_MAX;
}

void verify(float* a, float* b, int size) {
    for(int i = 0; i<size; i++) {
        if (abs(a[i] - b[i]) > 1.0e-5) {
            printf("Element %d does not match: %f != %f", i, a[i], b[i]);
            break;
        }
    }
}

int main(int argc, char* argv[]) {

    int array_size = 1<<20;

    // Allocate arrays
    float* a = (float*)malloc(array_size * sizeof(float));
    float* b = (float*)malloc(array_size * sizeof(float));
    
    // Initialize with some random data
    random_init(a, array_size);

    // Compute on GPU
    #pragma acc data copyin(a[0:array_size]) copyout(b[0:array_size])
    {   
        #pragma acc parallel loop
        for (int i = 0; i<array_size; ++i) {
            b[i] = a[i]*a[i];
        }
    }

    // Verify the result
    verify(a, b, array_size);

    free(a);
    free(b);
    
    return 0;
}