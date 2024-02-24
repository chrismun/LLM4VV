#include <iostream>
#include <cstdlib>
#include <ctime>
#include "acc_testsuite.h"

#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000;
    int a[N], b[N], c[N];

    // Initialize arrays
    for(int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Perform vector addition
    #pragma acc kernels copyin(a[0:N], b[0:N]), copyout(c[0:N])
    for(int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for all kernels to finish
    #pragma acc wait

    // Check the results
    for(int i = 0; i < N; i++) {
        if(c[i] != a[i] + b[i]) {
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