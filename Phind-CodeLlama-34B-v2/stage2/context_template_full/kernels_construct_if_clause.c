#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
#define T1 256
/*T1:kernels construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int n = T1;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() % 100;
        b[x] = a[x];
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc kernels if(acc_on_device(acc_device_nvidia))
        {
            for (int x = 0; x < n; ++x) {
                if (a[x] < 50) {
                    a[x] += 1;
                }
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (b[x] < 50) {
            b[x] += 1;
        }
        if (a[x] != b[x]) {
            err = 1;
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