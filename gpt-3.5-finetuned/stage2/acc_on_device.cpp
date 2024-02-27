#include "acc_testsuite.h"
#ifndef T1
//T1:acc on device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_on_device(acc_get_device_type()) == acc_device_none){
        constexpr unsigned int num_gang = 10;
        constexpr unsigned int num_worker = 32 * 8;
        unsigned int *a = (unsigned int *)malloc(num_gang * num_worker * sizeof(unsigned int));

        for (unsigned int x = 0; x < num_gang * num_worker; ++x){
            a[x] = x;
        }
        #pragma acc data copy(a[0:num_gang * num_worker])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (unsigned int x = 0; x < num_gang; ++x){
                    #pragma acc loop
                    for (unsigned int y = 0; y < num_worker; ++y){
                        a[x * num_worker + y] += 1;
                    }
                }
            }
        }

        for (unsigned int x = 0; x < num_gang; ++x){
            for (unsigned int y = 0; y < num_worker; ++y){
                if (a[x * num_worker + y] != y + num_worker * x + 1){
                    err = 1;
                }
            }
        }

        return err;
    }
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