#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc wait,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int async = acc_async_noval;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    acc_init(a, n * sizeof(int));
    acc_init(b, n * sizeof(int));
    acc_init(c, n * sizeof(int));

    #pragma acc data copy(a[0:n], b[0:n], c[0:n]) async(async)
    {
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
        {
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + b[x];
            }
        }
    }

    acc_wait(async);

    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION) {
            err = 1;
        }
    }

    free(a);
    free(b);
    free(c);

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