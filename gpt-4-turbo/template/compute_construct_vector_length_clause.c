#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int vector_length = 64; // Example vector length
    const int data_size = 1024; // Size of data to operate on
    int *a = (int *)malloc(data_size * sizeof(int));
    int *b = (int *)malloc(data_size * sizeof(int));
    int *c = (int *)malloc(data_size * sizeof(int));

    // Initialize arrays with random data
    for(int i = 0; i < data_size; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0; // Initialize output array
    }

    // Compute vector addition with specified vector length
#pragma acc parallel loop vector_length(vector_length)
    for(int i = 0; i < data_size; i++){
        c[i] = a[i] + b[i]; // Simple vector operation to test
    }

    // Check for errors
    for(int i = 0; i < data_size; i++){
        if(c[i] != (a[i] + b[i])){
            err++;
            break; // Error found, no need to check further
        }
    }

    free(a);
    free(b);
    free(c);

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