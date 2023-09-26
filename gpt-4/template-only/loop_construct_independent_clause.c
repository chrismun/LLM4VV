#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
// T1: loop construct independent clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    int arr_length = 1000;
    float a[arr_length]; 
    float b[arr_length];
    for (int i = 0; i < arr_length; i++) {
        a[i] = (float)rand()/(float)(RAND_MAX/10.0);
    }
    #pragma acc parallel loop 
    for (int i = 0; i < arr_length; i++) {
        b[i] = a[i] * a[i];
    }

    for (int i = 0; i < arr_length; i++) {
        if (b[i] != a[i] * a[i]){
            err = 1;
            break;
        }
    }

    return err;
}
#endif

int main() {
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