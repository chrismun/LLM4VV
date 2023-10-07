#include "acc_testsuite.h"
#ifndef T1
// T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;
    const int n = 1024;
    int *a = (int*)malloc(sizeof(int) * n);
    int *b = (int*)malloc(sizeof(int) * n);

    // Initialize data
    for (int i = 0; i < n; i++){
        a[i] = i;
        b[i] = -1;
    }

#pragma acc data copyin(a[0:n]) copyout(b[0:n])
#pragma acc parallel loop cache(a[0:n])
    for (int i = 0; i < n; i++){
        b[i] = a[i] * a[i];
    }

    // Verify results
    for (int i = 0; i < n; i++){
        if (b[i] != a[i] * a[i]){
            err = 1;
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