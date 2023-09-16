#include "acc_testsuite.h"
#include <openacc.h>

#define ACC_DEVICE_TYPE acc_device_nvidia

#ifndef ASYNC_TEST
#define ASYNC_TEST

#define N 50000000
float a[N];

void init() {
    for(int i=0; i<N; i++) {
        a[i] = (float)i;
    }
}

void compute() {
    int n = N;
    #pragma acc kernels loop copy(a[0:n]) async
    for(int i=0; i<n; i++) {
        a[i] += 0.5f;
    }
}

int test(){
    int err = 0;

    acc_init(ACC_DEVICE_TYPE);
    init();
    compute();

    if(acc_async_test(-1)) { // The computation should not finish instantaneously
        err = 1;
    }

    acc_shutdown(ACC_DEVICE_TYPE);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    #ifndef ASYNC_TEST

    failed = test();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;

    #else
    printf("ASYNC_TEST is defined\n");
    return 0;
    #endif
}