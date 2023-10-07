#include "acc_testsuite.h"
#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));
    int *d = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
        c[i] = 0;
        d[i] = 0;
    }

    #pragma acc data deviceptr(a, b, c, d)
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            d[i] = a[i] - b[i];
        }
    }

    // Verify the results
    for (int i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i] || d[i] != a[i] - b[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}