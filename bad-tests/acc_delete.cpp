#include "acc_testsuite.h"

/*Test acc delete,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);

    // Initialize a data array in local memory
    size_t bytes = sizeof(int) * 100;
    int* data_arg = new int[100];
    for(int i = 0; i < 100; i++) {
        data_arg[i] = rand() % 100;
    }
  
    // Copy the data array to device memory
    #pragma acc enter data copyin(data_arg[0:100])

    // Use the data array in a simple OpenACC compute construct
    #pragma acc parallel loop copyout(data_arg[0:100])
    for(int i = 0; i < 100; i++) {
        data_arg[i] = data_arg[i] * 2;
    }
  
    // Delete the data array from device memory using acc_delete routine
    acc_delete(data_arg, bytes);

    // Check if the memory has been indeed deleted from the device
    #pragma acc parallel loop copyout(data_arg[0:100])
    for(int i = 0; i < 100; i++) {
        if (data_arg[i] != 0) {
            err = 1;
            break;
        }
    }

    delete[] data_arg;  // clean up host memory 

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
  
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}