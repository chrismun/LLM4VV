#include "acc_testsuite.h"

#ifndef T1
// T1: compute construct vector_length clause, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int a[n], b[n], c[n];

    for(int i = 0; i < n; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

#pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
#pragma acc parallel loop collapse(1) vector_length(4)
    for(int i = 0; i < n; i++){
        c[i] = a[i] + b[i];
    }

    for(int i = 0; i < n; i++){
        if(c[i] != a[i] + b[i]){
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