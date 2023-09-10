#include "acc_testsuite.h"
#ifndef T1
//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *a_copy = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    d_int *devtest, *devrand;

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        a_copy[x] = 1;
        b[x] = 1;
    }

    devtest = (int *)acc_create(a, n * sizeof(int));
    devrand = (int *)acc_copyin(a_copy, n * sizeof(int));

    #pragma acc target device(acc_get_device_num(0))
    #pragma acc parallel present(devtest[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            devtest[x] = devtest[x] + devrand[x];
        }
    }

    acc_copyout(a, n * sizeof(int));
    #pragma acc exit data copyout(a[0:n])
    for (int x = 0; x < n; ++x){
        if (a[x] < 2){
            err += 1;
        }
    }
    #pragma acc exit data delete(a[0:n], devrand[0:n])
    if (err != 0){
        return 1;
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