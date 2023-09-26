#include "acc_testsuite.h"
#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;
    int async_id = 1;
    int dev_num = acc_get_device_num(acc_device_nvidia);

    // Initialize data
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
    for (int x = 0; x < n; ++x) {
        a[x] = x;
        b[x] = x * 2;
        c[x] = 0;
    }

    // Create async copy
    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n]) async(async_id)
    #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(async_id)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            c[x] = a[x] + b[x];
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n]) copyout(c[0:n]) async(async_id)

    // Test acc_async_test
    if (acc_async_test(async_id) == 0) {
        err = 1;
    }

    // Wait for async operation to complete
    acc_async_wait(async_id);

    // Check result
    for (int x = 0; x < n; ++x) {
        if (c[x] != a[x] + b[x]) {
            err = 1;
        }
    }

    // Cleanup
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