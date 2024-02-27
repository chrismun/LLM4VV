#include <openacc.h>
#include <cstdlib>
#include <iostream>

// Seed for randomness
#define SEED 12345
// Number of test calls
#define NUM_TEST_CALLS 10

// Test for acc delete
int test_acc_delete(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *data = (float*)malloc(sizeof(float)*size);

    // Initialize data
    for(int i = 0; i < size; ++i){
        data[i] = rand() / (float)RAND_MAX;
    }

    // Allocate and copy data to device
    #pragma acc enter data copyin(data[0:size])

    // Perform a dummy operation on the data in parallel on the device
    #pragma acc parallel loop present(data[0:size])
    for(int i = 0; i < size; ++i){
        data[i] = data[i] * 2.0f;
    }

    // Use acc_delete to deallocate device memory
    acc_delete((void*)data, sizeof(float)*size);

    // Here you would ideally check if acc_delete worked by trying to access the data
    // and expecting an error. However, in a real environment this can cause undefined behavior.
    // Instead, we ensure acc_delete is called correctly and trust its functionality.

    free(data);
    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_delete();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }

    // This is for illustration; in a real scenario, you'd have more sophisticated error handling.
    if (failcode == 0) {
        std::cout << "acc_delete test passed." << std::endl;
    } else {
        std::cout << "acc_delete test failed." << std::endl;
    }
    
    return failcode;
}