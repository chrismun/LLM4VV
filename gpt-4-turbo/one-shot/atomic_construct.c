#include "acc_testsuite.h"
#ifndef T_ATOMIC
// T_ATOMIC:kernels,parallel,atomic,V:1.0-2.7
int test_atomic() {
    int err = 0;
    const int num_iterations = 10000;
    int *counter = (int *)malloc(sizeof(int));
    *counter = 0;

    #pragma acc parallel num_gangs(1) vector_length(128)
    {
        #pragma acc loop
        for (int x = 0; x < num_iterations; ++x) {
            #pragma acc atomic update
            *counter += 1;
        }
    }

    if (*counter != num_iterations) {
        err += 1;
    }

    free(counter);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T_ATOMIC
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test_atomic();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}