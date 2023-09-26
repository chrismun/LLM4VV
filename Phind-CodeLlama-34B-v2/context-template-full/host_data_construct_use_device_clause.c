#include <stdio.h>
#include <stdlib.h>
#include <OpenACC.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:host_data construct use_device clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 100;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));
    int *c = (int *)malloc(N * sizeof(int));

    for (int x = 0; x < N; ++x) {
        a[x] = rand() % 100;
        b[x] = rand() % 100;
    }

    #pragma acc enter data copyin(a[0:N], b[0:N])
    #pragma acc host_data use_device(a, b)
    {
        for (int x = 0; x < N; ++x) {
            c[x] = a[x] + b[x];
        }
    }
    #pragma acc exit data copyout(c[0:N])

    for (int x = 0; x < N; ++x) {
        if (c[x] != a[x] + b[x]) {
            err = 1;
            break;
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