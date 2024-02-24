#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data;
    int *device_data;
    int size = 1024;

    host_data = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        host_data[i] = i;
    }

    acc_init(acc_device_nvidia);

    acc_malloc(&device_data, size * sizeof(int));
    acc_memcpy_to_device(device_data, host_data, size * sizeof(int));

    int structured_ref_count = acc_get_ref_count(device_data, acc_get_device_num(acc_device_nvidia), acc_structured_ref_count);
    int dynamic_ref_count = acc_get_ref_count(device_data, acc_get_device_num(acc_device_nvidia), acc_dynamic_ref_count);

    if (structured_ref_count != 1 || dynamic_ref_count != 0) {
        err = 1;
    }

    acc_copyout(host_data, size * sizeof(int));
    acc_free(device_data);

    structured_ref_count = acc_get_ref_count(device_data, acc_get_device_num(acc_device_nvidia), acc_structured_ref_count);
    dynamic_ref_count = acc_get_ref_count(device_data, acc_get_device_num(acc_device_nvidia), acc_dynamic_ref_count);

    if (structured_ref_count != 0 || dynamic_ref_count != 0) {
        err = 1;
    }

    free(host_data);

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