#include "acc_testsuite.h"

// Test acc_create
int test_acc_create() {
    int error = 0;
    srand(SEED);

    // Create a size for the data
    size_t data_size = 100 * sizeof(float);

    // Use acc_create to allocate data on the device
    void* device_data = acc_create(NULL, data_size);
      
    // Test if the pointer to the allocated device memory is not null
    if (device_data == NULL) {
        error = 1;
    }
    
    return error;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test_acc_create();
    }
    
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}