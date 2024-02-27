#include "acc_testsuite.h"
#ifndef T2
// T2: data, data-deviceptr, V:1.0-2.7
int test2() {
    int err = 0;
    srand(SEED);
    real_t *a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_device, *b_device;

    // Populating the host array
    for (int x = 0; x < n; ++x) {
        a_host[x] = rand() / (real_t)(RAND_MAX / 10);
        b_host[x] = 0;
    }

    // Allocate memory on the device and copy data from the host
    a_device = (real_t *)acc_malloc(n * sizeof(real_t));
    b_device = (real_t *)acc_malloc(n * sizeof(real_t));
    acc_memcpy_to_device(a_device, a_host, n * sizeof(real_t));

    // Use the deviceptr clause to inform the compiler that data is already on the device
    #pragma acc data present(a_device[0:n]) deviceptr(b_device)
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x) {
            b_device[x] = a_device[x];
        }
    }

    // Copy back the data to host and verify
    acc_memcpy_from_device(b_host, b_device, n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        if (fabs(b_host[x] - a_host[x]) > PRECISION) {
            err += 1;
        }
    }

    // Cleanup
    acc_free(a_device);
    acc_free(b_device);
    free(a_host);
    free(b_host);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test2();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1); // Assuming a bit position for each test
    }
#endif

    return failcode;
}