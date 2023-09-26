#include "acc_testsuite.h"
#ifndef T1
/*T1:async clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));

    // initialize data
    for(int i = 0; i < size; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc parallel async
        {
            for (int i = 0; i < size; i++) {
                b[i] = a[i] * 2;
            }
        }

        #pragma acc update host(b[0:size]) async(1)

        #pragma acc wait

        // check results
        for (int i = 0; i < size; i++) {
            if (b[i] != a[i] * 2) {
                err = 1;
            }
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