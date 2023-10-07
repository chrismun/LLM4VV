#include "acc_testsuite.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

#define ARR_SIZE 1000
#define SEED 12345

int test_serial_construct() {
    int *h_arr = new int[ARR_SIZE];
    int *res_arr = new int[ARR_SIZE];
    int err = 0;

    srand(SEED);
    // Initialize on host
    for (int i = 0; i < ARR_SIZE; i++) {
        h_arr[i] = i;
    }

    #pragma acc data copyin(h_arr[0:ARR_SIZE]) copyout(res_arr[0:ARR_SIZE])
    {
        #pragma acc serial 
        {
            for (int i = 0; i < ARR_SIZE; i++) {
                res_arr[i] = h_arr[i]*2;
            }
        }
    }

    // Correctness check
    for (int i = 0; i < ARR_SIZE; i++) {
        if (res_arr[i] != h_arr[i]*2) {
            err++;
        }
    }

    delete[] h_arr;
    delete[] res_arr;

    return err;
}

int main() {

    int res = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        res += test_serial_construct();
    }

    if (res != 0) {
        std::cerr << "Serial construct test failed!" << std::endl;
        return 1;
    }

    std::cout << "Serial construct test passed!" << std::endl;
    return 0;
}