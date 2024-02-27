#include "acc_testsuite.h"
#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int struct_ref_count = 0;
    int *a = (int *)malloc(n * sizeof(int));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    int *dev_test = (int *)malloc(n * sizeof(int));
    dev_test[0] = 1;
    #pragma acc enter data copyin(dev_test[0:1])
    #pragma acc kernels loop
    for (int i = 0; i < n; ++i){
        dev_test[i] = 0;
    }
    #pragma acc exit data copyout(dev_test[0:1])
    for (int x = 0; x < n; ++x){
        if (dev_test[x] != 0){
            struct_ref_count = struct_ref_count + 1;
        }
    }

    for (int x = 0; x < LOOPS; ++x){
        struct_ref_count = 1;

        for (int y = 0; y < n; ++y){
            a[y] = rand() / (real_t)(RAND_MAX / 10);
            b[y] = rand() / (real_t)(RAND_MAX / 10);
        }
        #pragma acc enter data copyin(a[0:n], b[0:n]) create(dev_test[0:1])
        *(dev_test) = 0;
        #pragma acc enter data copyin(dev_test[0:1])
        #pragma acc kernels loop present(a[0:n], b[0:n])
        for (int y = 0; y < n; ++y){
            a[y] = a[y] + b[y];
        }
        #pragma acc exit data delete(a[0:n], b[0:n])
        #pragma acc exit data copyout(dev_test[0:1])
        for (int y = 0; y < n; ++y){
            if (a[y] != 0){
                err += 1;
            }
        }
    }

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