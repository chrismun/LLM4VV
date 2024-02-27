#include "acc_testsuite.h"
#ifndef T1
// T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Try to set device number to 0 (assuming at least one acc device)
    acc_set_device_num(0, acc_device_none);

    // Now, verify if the device was set correctly
    int device_num = acc_get_device_num(acc_device_none);
    if (device_num != 0) {
        err++;
    }
    
    // Implement a very simple operation to confirm the device works
    int host_data = 1;
    int *device_data;
    device_data = (int*) acc_malloc(sizeof(int));
    acc_memcpy_to_device(device_data, &host_data, sizeof(int));

    int back_data = 0;
    acc_memcpy_from_device(&back_data, device_data, sizeof(int));
    if (back_data != host_data) {
        err++;
    }
    
    acc_free(device_data);

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