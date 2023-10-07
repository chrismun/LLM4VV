#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Array size
    unsigned int N = 10000;

    // Create and fill an array with random values
    int *a = (int*) malloc(N * sizeof(int));
    for(int i=0; i<N; i++) {
        a[i] = rand();
    }

    // Process Array serially
    // Making sure that openacc will not attempt to parallelize this loop
    #pragma acc serial
    for(int i=0; i<N; i++) {
        a[i] *= 2;
    }

    // Check values in parallel
    #pragma acc parallel loop reduction(+:err)
    for(int i=0; i<N; i++) {
        if (a[i] != 2*(a[i]/2)) {
            err += 1;
        }
    }

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