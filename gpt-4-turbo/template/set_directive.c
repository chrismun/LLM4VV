#include "acc_testsuite.h"
#ifndef T1
//T1:set,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int * a = (int *)malloc(size * sizeof(int));
    int * b = (int *)malloc(size * sizeof(int));

    // Initialize the arrays
    for (int i = 0; i < size; ++i){
        a[i] = rand() / (RAND_MAX / 100);
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i){
            b[i] = a[i];
        }
    }

    // Verify the results
    for (int i = 0; i < size; ++i){
        if (b[i] != a[i]){
            ++err;
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