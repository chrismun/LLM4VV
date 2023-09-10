#include "acc_testsuite.h"
#include <cstdlib>
#include <openacc.h>

#ifndef T1
/*T1:acc deviceptr,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize a variable on the host
    int* host_data = (int*)malloc(sizeof(int));
    *host_data = 42;

    // Copy the data to the device and get its address
    acc_copyin(host_data, sizeof(int));
    void *device_ptr = acc_deviceptr(host_data);

    // Test if the device pointer is not null
    if (device_ptr == NULL) {
        err = 1;
    }

    // Test if the device pointer points to the correct data
    if (!err){
        int *temp = (int*)malloc(sizeof(int));
        acc_memcpy_from_device(temp, device_ptr, sizeof(int));
        if(*temp != *host_data) {
            err = 1;
        }
        free(temp);
    }

    acc_delete(host_data, sizeof(int));
    free(host_data);

    return err;
}
#endif

int main() {
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