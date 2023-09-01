#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Generate random data for the vector clause
    int n = rand() % 100 + 1;
    int a[n];
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    // Use the vector clause to compute the sum of the elements in the array
    int sum = 0;
    #pragma acc parallel loop vector(a) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    // Check that the sum is correct
    if (sum != (n * (n + 1)) / 2) {
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