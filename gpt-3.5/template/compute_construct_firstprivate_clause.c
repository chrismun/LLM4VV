#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Define variables
    int a = 0;
    int b = 0;

    // Compute construct with firstprivate clause
    // Compute the sum of a and b using parallel execution on GPU
    #pragma acc parallel loop num_gangs(1) num_workers(1) vector_length(1) firstprivate(a,b)
    for (int i = 0; i < 1000; i++) {
        a += i;
        b += i;
    }

    // Verify correctness
    int expected_sum = (999 * 1000) / 2;
    if (a != expected_sum || b != expected_sum) {
        err = 1;
    }

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