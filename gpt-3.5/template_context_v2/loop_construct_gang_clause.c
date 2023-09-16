#include "acc_testsuite.h"
#ifndef T1
//T1: loop construct gang clause, V:2.7-3.3
int test1(){
    int err = 0;
    int n = 100;

    // Allocate memory on host
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    // Initialize input arrays
    for(int i = 0; i < n; i++){
        a[i] = i;
        b[i] = 0;
    }

    // Compute on accelerator
    #pragma acc parallel loop gang
    for(int i = 0; i < n; i++){
        b[i] = a[i] * a[i];
    }

    // Verify the result
    for(int i = 0; i < n; i++){
        if(b[i] != a[i] * a[i]){
            err = 1;
            break;
        }
    }

    // Free allocated memory
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
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}