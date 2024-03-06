#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 100;
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Perform operation using seq clause
    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc loop seq
        for (i = 0; i < N; ++i) {
            c[i] = a[i] + b[i];
        }
    }

    // Verify results
    for (i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
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