#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>

#ifndef NUM_ELEMENTS
#define NUM_ELEMENTS 1024
#endif

#ifndef PRECISION
#define PRECISION 1e-5
#endif

// Utility function to check error after kernel execution
int check_data(real_t* a, real_t* b, int n) {
    int err = 0;
    for (int i = 0; i < n; ++i) {
        if (fabs(a[i] - b[i]) > PRECISION) {
            err++;
        }
    }
    return err;
}

int test_reference_counters() {
    int err = 0;
    real_t* host_data = (real_t*)malloc(NUM_ELEMENTS * sizeof(real_t));
    real_t* device_check = (real_t*)malloc(NUM_ELEMENTS * sizeof(real_t));

    // Initialize host data
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        host_data[i] = (real_t)i;
    }

    // Using OpenACC to allocate and initialize device memory
    #pragma acc data create(host_data[0:NUM_ELEMENTS])
    {
        // Increment structured reference counter
        #pragma acc parallel present(host_data[0:NUM_ELEMENTS])
        {
            #pragma acc loop
            for (int i = 0; i < NUM_ELEMENTS; i++) {
                host_data[i] += 1;
            }
        }

        // The structured reference counter is implicitly decremented here at the end of the data region
    }

    // Using API call to increment dynamic reference counter explicitly
    acc_copyin(host_data, NUM_ELEMENTS * sizeof(real_t));
    
    // Copy back to check if modifications done above are present
    acc_copyout(host_data, NUM_ELEMENTS * sizeof(real_t));

    // Copy to host to verify
    #pragma acc update host(device_check[0:NUM_ELEMENTS])

    // Decrement dynamic reference counter explicitly
    acc_delete(host_data, NUM_ELEMENTS * sizeof(real_t));

    err = check_data(host_data, device_check, NUM_ELEMENTS);

    free(host_data);
    free(device_check);
    return err;
}

int main() {
    int failCode = 0;
    if (test_reference_counters() != 0) {
        failCode = 1;
    }
    printf("Test %s.\n", failCode == 0 ? "PASSED" : "FAILED");
    return failCode;
}