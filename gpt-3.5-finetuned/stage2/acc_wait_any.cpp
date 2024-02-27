#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Check acc_async_test
    int queues = acc_get_num_queues(acc_get_device_type());
    int *asyncs = (int *)malloc(queues*sizeof(int));
    for (int x = 0; x < queues; ++x){
        asyncs[x] = acc_async_test(x);
    }
    #pragma acc data copyin(asyncs[0:queues])
    {
        #pragma acc kernels
        {
            for (int x = 0; x < queues; ++x){
                if (asyncs[x] != acc_async_sync){
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        a[y] += 1;
                    }
                }
            }
        }
    }

    int counter = 0;
    int *waiters = (int *)malloc(queues*sizeof(int));
    for (int x = 0; x < queues; ++x){
        if (asyncs[x] != acc_async_sync){
            waiters[counter++] = asyncs[x];
        }
    }
    for (int x = 0; x < NUM_ITERATIONS; ++x){
        int returned = acc_wait_any(counter, waiters);
        if (returned < 0){
            err += 1;
        }
        else {
            for (int y = 0; y < acc_get_num_queues(acc_get_device_type()); ++y){
                if (returned == asyncs[y]){
                    #pragma acc update host(a[0:n])
                    for (int z = 0; z < n; ++z){
                        if (fabs(a[z] - 2) > PRECISION){
                            err += 1;
                            break;
                        }
                    }
                }
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