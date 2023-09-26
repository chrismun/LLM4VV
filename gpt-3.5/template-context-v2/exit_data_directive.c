#include "acc_testsuite.h"
#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc exit data delete(a[0:N])      // Delete data on device
        #pragma acc exit data copyout(b[0:N])     // Copy data back to host
    }

    for(int i = 0; i < N; i++){
        if(a[i] != 0){
            err = 1;
            break;
        }
        if(b[i] != i){
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