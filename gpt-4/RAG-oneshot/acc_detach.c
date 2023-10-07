#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1000
#define VAL 5.0

void initialize(double *data, int size) {
    for(int i=0; i<size; i++)
        data[i] = (double) i;
}

int main() {
    // Create data on the host
    double *x = (double*)malloc(SIZE*sizeof(double));
    double *y = (double*)malloc(SIZE*sizeof(double));
    
    initialize(x, SIZE);

    // Transfer 'x' to device
    #pragma acc enter data copyin(x[0:SIZE])

    // attach 'y'
    acc_attach((void**)&y);

    // Perform a computation on the GPU
    #pragma acc parallel loop present(x[0:SIZE], y[0:SIZE])
    for(int i=0; i<SIZE; i++) {
        y[i] = x[i] * VAL;
    }

    // Now detach 'y'
    acc_detach((void**)&y);
    
    // Transfer 'y' from device to host
    #pragma acc exit data copyout(y[0:SIZE])

    // Validate the results
    for(int i=0; i<SIZE; i++) {
        if(y[i] != x[i] * VAL) {
            printf("Result validation failed at element %d! Expected %f but got %f\n", i, x[i] * VAL, y[i]);
            return 1;
        }
    }

    printf("Result validation successful! All elements correctly calculated.\n");

    return 0;
}