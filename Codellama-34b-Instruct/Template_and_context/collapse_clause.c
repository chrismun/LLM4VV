c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int a[N];
    int tanI[N];

    // Initialize the input array
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Compute the tangent of each element in the input array
    #pragma acc parallel loop collapse(force:2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tanI[i] = tan(a[i]);
        }
    }

    // Check that the tangent of each element in the input array is correct
    for (int i = 0; i < N; i++) {
        if (tanI[i] != tan(a[i])) {
            err = 1;
            break;
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