#include "acc_testsuite.h"
#include <openacc.h>
#ifndef T1
/*T1:acc async test,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int async_queue = rand() % 2;
    int wait_arg = async_queue;
    int dev_num = acc_get_device_num(acc_get_device_type());

    acc_init(acc_device_nvidia);

    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n]) async(async_queue)
        {
            for (int x = 0; x < n; ++x) {
                a[x] = x * x;
            }
        }

        #pragma acc parallel present(a[0:n], b[0:n]) async(async_queue)
        {
            for (int x = 0; x < n; ++x) {
                b[x] = a[x] * 2;
            }
        }
    }

    if (acc_async_test(wait_arg) == 0) {
        err = 1;
    }

    if (acc_async_test_device(wait_arg, dev_num) == 0) {
        err = 1;
    }

    if (acc_async_test_all() == 0) {
        err = 1;
    }

    if (acc_async_test_all_device(dev_num) == 0) {
        err = 1;
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