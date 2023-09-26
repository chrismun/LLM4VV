#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define ARRAY_SIZE 100
#define NUM_TEST_CALLS 10

int test_memcpy_d2d() {
    int err = 0;
    int array_size = ARRAY_SIZE;
    int srcDevice = acc_get_device_num(acc_device_not_host);
    int destDevice;
 
    if (srcDevice == acc_get_num_devices(acc_device_not_host) - 1) {
        destDevice = 0;
    }
    else {
        destDevice = srcDevice + 1;
    }

    float *src = (float*)acc_malloc(array_size * sizeof(float));
    float *dest = (float*)acc_malloc(array_size * sizeof(float));

    acc_set_device_num(srcDevice, acc_device_not_host);
    #pragma acc parallel loop present(src[0:array_size])
    for (int i = 0; i < array_size; i++) {
        src[i] = (float) i;
    }

    acc_memcpy_d2d(dest, src, array_size * sizeof(float), destDevice, srcDevice);

    acc_set_device_num(destDevice, acc_device_not_host);
    #pragma acc parallel loop present(dest[0:array_size])
    for (int i = 0; i < array_size; i++) {
        if (dest[i] != (float) i) {
            err = 1;
        }
    }

    acc_free(src);
    acc_free(dest);
    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_memcpy_d2d();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}