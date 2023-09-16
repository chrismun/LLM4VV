#include "acc_testsuite.h"

#ifndef T1
// T1: variable predetermined data attributes, V:2.7-3.3
int test1(){
    int err = 0;
    int length = 100;
    int *a = (int *)malloc(length * sizeof(int));

    #pragma acc data create(a[0:length])
    {
        #pragma acc parallel loop present(a[0:length])
        for (int i = 0; i < length; i++) {
            a[i] = i;
        }

        #pragma acc parallel loop present(a[0:length])
        for (int i = 0; i < length; i++) {
            if (a[i] != i) {
                err = 1;
                break;
            }
        }
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}