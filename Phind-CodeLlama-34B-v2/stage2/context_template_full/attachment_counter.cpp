#include "acc_testsuite.h"
#ifndef T268
#define T268

int test268(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int *)malloc(sizeof(int));
    int *device_ptr = (int *)acc_malloc(sizeof(int));

    // Attach host_ptr to device_ptr
    acc_attach(host_ptr, device_ptr, sizeof(int));

    // Check if attachment counter is incremented
    if(acc_get_attach_counter(host_ptr) != 1){
        err = 1;
    }

    // Detach host_ptr from device_ptr
    acc_detach(host_ptr);

    // Check if attachment counter is decremented
    if(acc_get_attach_counter(host_ptr) != 0){
        err = 1;
    }

    acc_free(device_ptr);
    free(host_ptr);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T268
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test268();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}