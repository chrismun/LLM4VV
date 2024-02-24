#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_threads = acc_get_num_devices(acc_device_nvidia);
    int my_id = acc_get_device_num(acc_device_nvidia);

    #pragma acc parallel num_gangs(1) num_workers(num_threads) vector_length(1)
    {
        int my_id_in_region = acc_get_device_num(acc_device_nvidia);
        if (my_id_in_region != my_id) {
            err = 1;
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