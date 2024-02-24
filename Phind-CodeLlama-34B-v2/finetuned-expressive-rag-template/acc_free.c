#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *data_dev;
    int data_host[10];

    // Allocate memory on the device
    data_dev = (int *)acc_malloc(10 * sizeof(int));
    if (data_dev == NULL) {
        fprintf(stderr, "acc_malloc failed\n");
        return 1;
    }

    // Copy data from host to device
    acc_memcpy_to_device(data_dev, data_host, 10 * sizeof(int));

    // Free memory on the device
    acc_free(data_dev);

    // Check if memory is still accessible
    acc_memcpy_from_device(data_host, data_dev, 10 * sizeof(int));

    // Check for errors
    err = acc_get_device_type() == acc_device_host ? 0 : 1;

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