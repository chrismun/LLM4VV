#include "acc_testsuite.h"
#ifndef T1
//T1:acc_memcpy_d2d,V:2.7-3.3
int test1(){
    int err = 0;
    int* a = (int*)malloc(N * sizeof(int));
    int* b = (int*)malloc(N * sizeof(int));
    int* c = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i + 1;
        c[i] = 0;
    }

    // Copy data from host to device
    #pragma acc enter data copyin(a[0:N], b[0:N])
    #pragma acc data copyout(c[0:N])
    {
        // Perform element-wise addition
        #pragma acc kernels
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Copy data from device to host
    #pragma acc exit data copyout(c[0:N]) delete(a[0:N], b[0:N])

    // Verify results
    for (int i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
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