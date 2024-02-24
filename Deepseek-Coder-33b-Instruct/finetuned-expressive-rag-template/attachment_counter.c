#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 1;

    #pragma acc data copyin(host_ptr[0:1])
    {
        int *device_ptr = host_ptr;

        // Test that the pointer is attached to a device address
        if (device_ptr != acc_deviceptr(host_ptr)) {
            err = 1;
        }

        // Test that the pointer is detached when the attachment counter reaches zero
        #pragma acc exit data delete(device_ptr)
        {
            if (device_ptr != NULL) {
                err = 1;
            }
        }
    }

    free(host_ptr);

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