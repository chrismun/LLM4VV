#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 1024;
    int a[array_size];
    int b[array_size];
    int correct[array_size];

    // Initialize arrays and set correct outcomes
    for (int i = 0; i < array_size; ++i) {
        a[i] = rand() % 100;
        b[i] = 1; // Increment by 1
        correct[i] = a[i] + 1; // Expected result after increment
    }

    // Parallel region using gang clause for loop distribution
    #pragma acc parallel num_gangs(512) vector_length(2)
    {
        #pragma acc loop gang
        for (int x = 0; x < array_size; ++x) {
            a[x] += b[x];
        }
    }

    // Check for errors
    for (int i = 0; i < array_size; ++i) {
        if (a[i] != correct[i]) {
            err++;
        }
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