#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>

#define N 1024
#define SEED 123
#define PRECISION 0.001

int main() {
    int errors = 0;
    size_t bytes = N * sizeof(float);
        
    // Allocate host memory
    float *hostArray = (float *)malloc(bytes);
    if (hostArray == NULL) {
        fprintf(stderr, "Failed to allocate host memory\n");
        return -1;
    }
    
    // Allocate device memory
    float *deviceArray = (float *)acc_malloc(bytes);
    if (deviceArray == NULL) {
        fprintf(stderr, "Failed to allocate device memory\n");
        free(hostArray);
        return -1;
    }
    
    // Initialize device memory
    #pragma acc parallel loop copy(deviceArray[0:N])
    for(int i = 0; i < N; i++) {
        deviceArray[i] = sin(i * 2.0 * M_PI / N);
    }
    
    // Copy data from device to host
    acc_memcpy_from_device(hostArray, deviceArray, bytes);
    
    // Verify the data
    #pragma acc parallel loop reduction(+:errors)
    for(int i = 0; i < N; i++) {
        float expected = sin(i * 2.0 * M_PI / N);
        if (fabs(hostArray[i] - expected) > PRECISION) {
            errors++;
        }
    }
    
    // Cleanup
    acc_free(deviceArray);
    free(hostArray);
    
    if (errors) {
        printf("Test FAILED: %d discrepancies found.\n", errors);
        return -1;
    } else {
        printf("Test PASSED.\n");
        return 0;
    }
}