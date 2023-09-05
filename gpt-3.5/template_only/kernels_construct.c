#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));
    int *c = (int *)malloc(N * sizeof(int));

    srand(SEED);
    
    // Initialize arrays
    for (int i = 0; i < N; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Compute multiplication of arrays
    #pragma acc kernels
    for (int i = 0; i < N; i++){
        c[i] = a[i] * b[i];
    }

    // Verify correctness of computation
    for (int i = 0; i < N; i++){
        if (c[i] != a[i] * b[i]){
            err = 1;
            break;
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
        failed += test1();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}