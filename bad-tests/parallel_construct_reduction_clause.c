#include "acc_testsuite.h"

int test_reduction_clause() {
    int err = 0;
    int original_sum = 0, parallel_sum = 0;
    int a[SIZE];

    // Initialization 
    for (int i = 0; i < SIZE; ++i) {
        a[i] = rand() % 100;
        original_sum += a[i];
    }

    #pragma acc parallel loop reduction(+:parallel_sum)
    for (int i = 0; i < SIZE; ++i) {
        parallel_sum += a[i];
    }

    // Test condition
    if (original_sum != parallel_sum) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    srand(SEED);

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_reduction_clause();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}