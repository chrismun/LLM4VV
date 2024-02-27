#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

// Seed for reproducibility
#define SEED 42
#define NUM_TEST_CALLS 10
#define N 10000

// Test function prototype
int test1();

int test1(){
    int err = 0;
    float a[N], b[N], c[N];
    bool is_acc_available = acc_get_num_devices(acc_device_not_host) > 0;

    srand(SEED);

    // Initialize arrays with some values
    for (int i = 0; i < N; i++){
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
        c[i] = 0.0f;
    }

    // OpenACC loop using the device_type clause
    #pragma acc parallel loop device_type(acc_device_not_host)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check results
    for (int i = 0; i < N; i++) {
        float expected = a[i] + b[i];
        if (c[i] != expected) {
            err++;
        }
    }

    // If there are no available accelerators, ensure 'err' is 0 only if falling back to host execution
    if (!is_acc_available && err != 0) {
        printf("Warning: No accelerator device found, but errors encountered on host execution.\n");
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }

    if (failed != 0){
        failcode += (1 << 0);
    }

    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}