#include "acc_testsuite.h"
#ifndef T1
//T1:{data_management},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 1024;
    int *a, *b;
    int *d_a, *d_b; // device pointers

    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));

    // Initialize arrays.
    for(int i = 0; i < N; ++i){
        a[i] = rand() % 100;
        b[i] = 0; // Will store the results
    }

    // Explicitly create space for 'a' on the device
    #pragma acc enter data copyin(a[0:N])
    // Also create space for 'b' but don't initialize since we'll write to it
    #pragma acc enter data create(b[0:N])

    // Now, perform a simple computation
    #pragma acc parallel present(a, b)
    {
        #pragma acc loop
        for(int i = 0; i < N; ++i){
            b[i] = a[i] + 1;
        }
    }

    // Copy back the result to host
    #pragma acc exit data copyout(b[0:N])

    // Check for errors
    for(int i = 0; i < N; i++){
        if(b[i] != a[i] + 1){
            err++;
        }
    }
    
    free(a);
    free(b);

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