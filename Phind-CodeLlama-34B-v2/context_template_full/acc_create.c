#include "acc_testsuite.h"
#ifndef T1
/*T1:acc create,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *devPtr = (int *)acc_create(a, n * sizeof(int));

    if (devPtr == NULL){
        err = 1;
    }

    acc_delete(devPtr, n * sizeof(int));
    free(a);

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