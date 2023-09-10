#include "acc_testsuite.h"
#include <iostream>

#define THREADS 1024
#define BLOCKS 1024

//Test function
__global__ void increment(int* sum){
    #pragma acc atomic
    *sum += 1;
}

int test1() {
    int err = 0;
    int* sum;
  
    // Allocate memory on the device
    cudaMallocManaged(&sum, sizeof(int));
    *sum = 0;

    increment<<<BLOCKS, THREADS>>>(sum);

    // Ensure all the additions have been done
    cudaDeviceSynchronize();

    // Check to see if additions are consistent
    if(*sum != (BLOCKS*THREADS)) {
        err = 1;
    }

    // Free the allocated memory
    cudaFree(sum);

    return err;
}

int main() {
    int failcode = 0;
    int failed;
  
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed){
          failcode = 1;
          std::cerr << "Test failed.\n";
          break;
        }
    }
    if(!failcode){
      std::cout << "All tests passed!\n";
    }
    return failcode;
}