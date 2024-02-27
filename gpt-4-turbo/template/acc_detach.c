#include "acc_testsuite.h"
#ifndef T1
// T1:{acc_detach},V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));
    int *host_b = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        b[i] = 0;
        host_b[i] = a[i];
    }

    #pragma acc data copy(a[0:size], b[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            b[i] = a[i] + 1;
        }

        #pragma acc detach
        {
            // The detached region should work independently but still see the updated `b`
            #pragma acc parallel loop
            for (int i = 0; i < size; ++i) {
                b[i] += 1;
            }
        } // End of detached region

        // Data in `b` should be updated in the data region even after detach
    }

    // Verifying results
    for (int i = 0; i < size; ++i) {
        host_b[i] += 2; // Simulating the operations done on the GPU or other accelerator
        if (b[i] != host_b[i]) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(host_b);
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