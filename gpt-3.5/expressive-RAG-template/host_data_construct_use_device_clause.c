#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    int *dev_a = (int *)malloc(n * sizeof(int));
    int *dev_b = (int *)malloc(n * sizeof(int));
    int *dev_c = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n]) create(dev_a[0:n], dev_b[0:n], dev_c[0:n])
    {
        #pragma acc enter data create(a[0:n], b[0:n], c[0:n])
        #pragma acc enter data copyin(a[0:n], b[0:n]) create(dev_a[0:n], dev_b[0:n]) // Copy data from host to device

        #pragma acc parallel loop present(dev_a[0:n], dev_b[0:n], dev_c[0:n])
        for (int i = 0; i < n; i++){
            dev_c[i] = dev_a[i] + dev_b[i];
        }

        #pragma acc exit data copyout(c[0:n]) // Copy data from device to host
    }

    for (int i = 0; i < n; ++i){
        if (c[i] != a[i] + b[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    free(dev_a);
    free(dev_b);
    free(dev_c);

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