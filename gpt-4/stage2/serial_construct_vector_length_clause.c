#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

int test1() {
    int err = 0;
    int array_size = 1024;
    int * a = (int*) malloc(array_size * sizeof(int));
    int * b = (int*) malloc(array_size * sizeof(int));
    int * c = (int*) malloc(array_size * sizeof(int));
    int * c_gpu = (int*) malloc(array_size * sizeof(int));  // To hold result from GPU

    // Initialize the arrays
    for(int i=0; i<array_size; i++) {
        a[i] = rand() % 1024;
        b[i] = rand() % 1024;
    }

    // Compute on CPU
    for(int i=0; i<array_size; i++)
        c[i] = a[i] + b[i];

    // Compute on GPU with vector_length clause
    #pragma acc parallel vector_length(128) copyin(a[0:array_size],b[0:array_size]) copyout(c_gpu[0:array_size])
    {
        #pragma acc loop vector
        for(int i=0; i<array_size; i++) {
            c_gpu[i] = a[i] + b[i];
        }
    }

    // Compare results
    for(int i=0; i<array_size; i++) {
        if(c[i] != c_gpu[i]) {
            err = 1;
            break;
        }
    }
    
    free(a);
    free(b);
    free(c);
    free(c_gpu);

    return err;
}

int main() {
    int errcode = 0;
    errcode += test1();
    return errcode;
}