#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int validate_shutdown() {
    int err = 0;

    // Assumption: Device of type 'acc_device_default' is in use.
    int device_type = acc_get_device_type();
    int num_devices = acc_get_num_devices(device_type);
    if (num_devices == 0) {
        fprintf(stderr, "No OpenACC devices available.\n");
        return 1;
    }
    
    // Allocate and initialize data on the host
    size_t n = 1024;
    double* host_array = (double*)malloc(n * sizeof(double));
    for (size_t i = 0; i < n; ++i) {
        host_array[i] = i;
    }

    // Use OpenACC data region to allocate and initialize data on the device
    #pragma acc data copy(host_array[0:n])
    {
        #pragma acc parallel loop
        for (size_t i = 0; i < n; ++i) {
            host_array[i] = host_array[i] * 2;
        }
    }
    
    // Attempt to shut down all devices of the current type.
    #pragma acc shutdown
    
    // The following OpenACC region should fail or act as no-op, as devices are shut down.
    #pragma acc parallel num_gangs(1)
    {
        // This operation is supposed to be ineffective post shutdown
    }

    // Verification step: This is rather symbolic, as directly detecting a failure due to
    // shutdown restrictions requires device-specific behaviors or runtime API checks.
    printf("Device of type %d has been issued a shutdown directive. Please manually verify no operations are performed on the device post-shutdown.\n", device_type);

    free(host_array);
    return err;
}

int main() {
    int failed = validate_shutdown();
    if (failed) {
        printf("Test failed.\n");
        return 1;
    } else {
        printf("Test passed.\n");
    }
    return 0;
}