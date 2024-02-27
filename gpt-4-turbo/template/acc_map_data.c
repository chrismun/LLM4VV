#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int *)malloc(size * sizeof(int));
    int *b = (int *)malloc(size * sizeof(int));
    // Initialize arrays
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Mapping data to device
    #pragma acc data copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i) {
            b[i] = a[i] + 1; // Simple computation to verify mapping
        }
    }
    
    // Verifying the result
    for(int i = 0; i < size; ++i) {
        if(b[i] != a[i] + 1) {
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