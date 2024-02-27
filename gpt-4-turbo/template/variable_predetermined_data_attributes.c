#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:private,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int *)malloc(size * sizeof(int));
    int *b = (int *)malloc(size * sizeof(int));

    // Initialize array 'a' with random values
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
    }

    // Compute in parallel - each thread should have a private copy of 'total'
    #pragma acc parallel num_gangs(1) vector_length(1024) copy(a[0:size], b[0:size])
    {
        int total = 0;
        #pragma acc loop reduction(+:total)
        for (int i = 0; i < size; ++i) {
            total += a[i];
        }
        b[acc_get_thread_num()] = total;
    }

    // Verify that 'total' was private and properly reduced in each thread
    int expected_total = 0;
    for (int i = 0; i < size; ++i){
        expected_total += a[i];
    }
    expected_total /= size; // Since we expect each thread to compute a portion of the total

    for (int i = 0; i < size; ++i) {
        if (b[i] != expected_total) {
            err++;
            break;
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