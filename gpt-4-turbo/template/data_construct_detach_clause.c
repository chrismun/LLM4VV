#include "acc_testsuite.h"
#ifndef T1
//T1:{data_construct_async},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a_host = (int*)malloc(size * sizeof(int));
    int *b_host = (int*)malloc(size * sizeof(int));

    // Initialize data
    for (int i = 0; i < size; ++i) {
        a_host[i] = rand() % 100;
        b_host[i] = 0;
    }

    // Perform offloaded operation asynchronously
    #pragma acc data copyin(a_host[0:size]) copyout(b_host[0:size]) async
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            b_host[i] = a_host[i] * 2;
        }
    }
    // Assuming a wait here for demonstration, though in practice this would be
    // more complex with real async workloads.
    #pragma acc wait

    // Validate results
    for (int i = 0; i < size; ++i) {
        if (b_host[i] != a_host[i] * 2) {
            err++;
        }
    }

    free(a_host);
    free(b_host);

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