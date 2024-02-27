#include <cstdlib>
#include <iostream>
#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct, async clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 10000;
    float *a = new float[size];
    float *b = new float[size];
    float *c = new float[size];

    // Initialize arrays
    for (int i = 0; i < size; ++i){
        a[i] = (float)rand()/(float)(RAND_MAX/100);
        b[i] = (float)rand()/(float)(RAND_MAX/100);
        c[i] = a[i]; // copy a into c for operation validation
    }

    // Apply operations in separate kernels regions asynchronously
    #pragma acc kernels async(1) copy(a[0:size])
    for (int i = 0; i < size; ++i){
        a[i] += 1.0f; // Simple operation 1
    }
    
    #pragma acc kernels async(2) copy(b[0:size])
    for (int i = 0; i < size; ++i){
        b[i] *= 2.0f; // Simple operation 2
    }

    // Wait for both asynchronous operations to complete
    #pragma acc wait(1)
    #pragma acc wait(2)

    // Verify the operations
    for (int i = 0; i < size; ++i){
        if (a[i] != c[i] + 1.0f){ // Check operation 1
            err++;
            break;
        }
        if (b[i] != c[i] * 2.0f){ // Assuming b initially equals a, check operation 2
            err++;
            break;
        }
    }

    delete[] a;
    delete[] b;
    delete[] c;

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}