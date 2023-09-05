#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)acc_malloc(sizeof(int) * N);
    int *b = (int *)acc_malloc(sizeof(int) * N);

    #pragma acc host_data use_device(a, b)
    {
        for (int i = 0; i < N; i++) {
            a[i] = i;
            b[i] = i;
        }
    }

    #pragma acc parallel loop device(a, b)
    for (int i = 0; i < N; i++) {
        a[i] += b[i];
    }

    #pragma acc parallel loop device(a, b)
    for (int i = 0; i < N; i++) {
        b[i] += a[i];
    }

    #pragma acc host_data use_device(a, b)
    {
        for (int i = 0; i < N; i++) {
            if (a[i] != b[i]) {
                err = 1;
                break;
            }
        }
    }

    acc_free(a);
    acc_free(b);

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