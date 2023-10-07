#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:data construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    #pragma acc data copy(a[0:10])
    {
        for (int x = 0; x < 10; ++x) {
            a[x] = rand() % 10;
        }

        #pragma acc parallel loop present(a[0:10])
        for (int x = 0; x < 10; ++x) {
            b[x] = a[x] * 2;
        }

        #pragma acc update host(b[0:10])

        for (int x = 0; x < 10; ++x) {
            if (b[x] != a[x] * 2) {
                err = 1;
                break;
            }
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