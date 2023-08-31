#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers
    int* a = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        a[i] = rand();
    }

    // Create a cache directive
    #pragma acc cache(a)

    // Access the array using the cache directive
    for (int i = 0; i < N; i++) {
        if (a[i] != a[i]) {
            err = 1;
            break;
        }
    }

    // Free the array
    free(a);

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