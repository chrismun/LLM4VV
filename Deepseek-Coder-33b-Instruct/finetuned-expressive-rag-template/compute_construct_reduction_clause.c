#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int*)malloc(N * sizeof(int));
    int sum = 0;
    int sum_expected = 0;

    // Initialize the array
    for(int i = 0; i < N; i++) {
        a[i] = i + 1;
        sum_expected += a[i];
    }

    // Compute the sum of the array
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < N; i++) {
        sum += a[i];
    }

    // Check if the results are the same
    if(sum != sum_expected) {
        err++;
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