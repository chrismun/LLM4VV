#include "acc_testsuite.h"
#ifndef T1
//T1:async clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
    int *d = (int *)malloc(n * sizeof(int));

    if (!a || !b || !c || !d) {
        err = 1;
        goto cleanup;
    }

    #pragma acc kernels
    {
        #pragma acc loop independent async
        for (int i = 0; i < n; i++) {
            a[i] = rand() % 100;
            b[i] = rand() % 100;
            c[i] = a[i] + b[i];
        }

        #pragma acc loop independent async
        for (int i = 0; i < n; i++) {
            d[i] = c[i] * 2;
        }
    }

    #pragma acc wait

    for (int i = 0; i < n; i++) {
        if (d[i] != (a[i] + b[i]) * 2) {
            err = 1;
            break;
        }
    }

cleanup:
    free(a);
    free(b);
    free(c);
    free(d);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}