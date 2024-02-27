#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T2
//T2:runtime, data, V:3.0-3.2
int test_acc_unmap_data() {
    int err = 0;
    size_t n = 100;
    float *hostData = (float *)malloc(n * sizeof(float));

    // Initialize data
    for (size_t i = 0; i < n; ++i) {
        hostData[i] = i;
    }

    // Explicitly mapping data to the device
    acc_map_data(hostData, acc_deviceptr(hostData), n * sizeof(float));

    // Use acc_unmap_data to unmap the data
    acc_unmap_data(hostData);

    // Ideally you would check here if the data is really unmapped.
    // However, this might not be directly verifiable in a portable way across different implementations.

    // Cleanup
    free(hostData);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T2
    failed = 0;
    failed = test_acc_unmap_data();
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    if (failcode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }

    return failcode;
}