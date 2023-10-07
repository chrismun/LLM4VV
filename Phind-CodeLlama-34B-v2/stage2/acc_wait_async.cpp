#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <openacc.h>

#ifndef T1
/*T1:acc wait async,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int async_arg = rand() % 2;
    int wait_arg = rand() % 2;
    int dev_num = acc_get_device_num(acc_device_nvidia);

    acc_init(acc_device_nvidia);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    acc_set_device_num(dev_num, acc_device_nvidia);

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc parallel async(async_arg)
        {
            for (int x = 0; x < n; ++x) {
                a[x] = x * x;
            }
        }

        #pragma acc parallel async(wait_arg)
        {
            for (int x = 0; x < n; ++x) {
                b[x] = a[x] * 2;
            }
        }

        acc_wait_async(wait_arg, async_arg);

        for (int x = 0; x < n; ++x) {
            if (b[x] != a[x] * 2) {
                err = 1;
                break;
            }
        }
    }

    free(a);
    free(b);

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