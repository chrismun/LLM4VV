#include "acc_testsuite.h"

#ifndef T1
// T1: data construct detach clause, V: 2.7-3.3
int test1() {
    int err = 0;

    // declare and initialize host and device arrays
    int* h_array = (int*)malloc(N * sizeof(int));
    int* d_array;

    for (int i = 0; i < N; i++) {
        h_array[i] = i;
    }

    #pragma acc enter data create(h_array[0:N])
    #pragma acc data present(h_array[0:N]) 
    {
        #pragma acc update device(h_array[0:N])
        d_array = h_array;
        
        #pragma acc exit data detach(d_array[0:N])

        #pragma acc update host(d_array[0:N])

        for (int i = 0; i < N; i++) {
            if (h_array[i] != i) {
                err = 1;
            }
        }
    }

    #pragma acc exit data delete(h_array[0:N])
    free(h_array);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}