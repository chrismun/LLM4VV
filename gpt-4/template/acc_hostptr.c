#include "acc_testsuite.h"

#ifndef T1
int test() {
    int err = 0;
    unsigned int *a_host;
    unsigned int *a_device;

    // Allocate memory for host and device
    a_host = (unsigned int*)malloc(SIZE*sizeof(unsigned int));
    #pragma acc enter data create(a_host[0:SIZE])

    // Initialize 'a_device' with host pointer reference using acc hostptr
    #pragma acc host_data use_device(a_host)
    {
        a_device = acc_deviceptr(a_host);
    }

    // Check data present on device
    if (acc_is_present(a_host, SIZE*sizeof(unsigned int)) == 0) {
        err = 1;
    }
    
    free(a_host);
    #pragma acc exit data delete(a_host)

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    srand(SEED);
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}