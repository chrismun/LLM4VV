#include "acc_testsuite.h"

int real_test(){

    int i;
    int async_val = acc_get_default_async();
    int async_val_async[acc_get_num_devices(acc_device_nvidia)];
    int async_val_host = -1;

    for (i = 0; i < acc_get_num_devices(acc_device_nvidia); ++i){
        async_val_async[i] = -1;
    }

    if (acc_get_device_type() == acc_device_nvidia){
        #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1) present(async_val_async[0:1]) async
        {
            async_val_async[0] = acc_get_default_async();
        }
    }
    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1) present(async_val) async
    {
        async_val[0] = acc_get_default_async();
    }
    async_val_host = acc_get_default_async();
    #pragma acc wait

    for (i = 1; i < acc_get_num_devices(acc_device_nvidia); ++i){
        if (async_val_async[0] != async_val_async[i]){
            return 1;
        }
    }
    if (async_val[0] == async_val_host){
        for (i = 1; i < acc_get_num_devices(acc_device_nvidia); ++i){
            if (async_val[0] != async_val_async[i]){
                return 1;
            }
        }
        return 0;
    }
    else {
        if (async_val[0] == async_val_async[0]){
            return 0;
        }
        return 1;
    }
}

int main(){

    int failcode;
    int failed;
    int count_failed = 0;
    int device_num, num_devices = acc_get_num_devices(acc_device_nvidia);;

    for (device_num = 0; device_num < num_devices; ++device_num){
        acc_set_device_num(device_num, acc_device_nvidia);
        failed = 0;

        for (int x = 0; x < NUM_TEST_CALLS; ++x){
            failed += real_test();
        }

        if (failed != 0){
            count_failed += 1;
        }
    }

    if (count_failed > 0){
        failcode = 0;
        for (int x = 2; x <= count_failed + 1; ++x){
            failcode += (int)pow(2, x);
        }

        return failcode;
    }
    return 0;