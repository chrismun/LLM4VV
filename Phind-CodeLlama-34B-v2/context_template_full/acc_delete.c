#include "acc_testsuite.h"
#ifndef T1
/*T1:acc delete,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *devPtr = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        devPtr[x] = a[x];
    }

    #pragma acc data copy(devPtr[0:n])
    {
        #pragma acc parallel present(devPtr[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                devPtr[x] = devPtr[x] * 2;
            }
        }
    }

    acc_delete(devPtr, n * sizeof(int));

    for (int x = 0; x < n; ++x){
        if (a[x] != devPtr[x]){
            err = 1;
        }
    }

    free(a);
    acc_free(devPtr);

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