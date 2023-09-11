#include <iostream>
#include <cstdlib>
#include <cstring>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Get the current device number
    int device_num = acc_get_device_num(ACC_DEVICE_TYPE_GPU);

    // Check if the device number is valid
    if (device_num < 0) {
        std::cerr << "Error: acc_get_device_num returned an invalid device number" << std::endl;
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}