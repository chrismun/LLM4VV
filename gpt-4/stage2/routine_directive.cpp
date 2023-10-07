#include "acc_testsuite.h"
#include <iostream>

// Function to add the corresponding elements of two arrays and store in a third one
#pragma acc routine seq
void vec_add(int n, float *a, float *b, float *c) {
    int i;
    #pragma acc loop
    for(i = 0; i < n; i++)
        c[i] = a[i] + b[i];
}

int test(){
    int n = 10000;
    float *a, *b, *c;

    // Allocate memory on host
    a = new float[n];
    b = new float[n];
    c = new float[n];

    bool err = false;

    // Initialize the arrays
    for(int i = 0; i < n; i++){
        a[i] = float(i);
        b[i] = float(i);
    }

    // Perform addition on device
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        vec_add(n, a, b, c);
    }

    // Check results
    for(int i = 0; i < n; i++) {
        if(c[i] != a[i] + b[i])
            err = true;
    }

    // Free up host memory
    delete[] a;
    delete[] b;
    delete[] c;

    return err;
}

int main(){
    int failcode = 0;
    
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test();
    }
    if (failed != 0){
        failcode = failcode + 1;
    }

    return failcode;
}