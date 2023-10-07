#include <iostream>
#include <cstdlib>
#include <cstring>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Set the device number to a random value
    int dev_num = rand() % 10;

    // Set the device type to a random value
    int dev_type = rand() % 2;

    // Call acc_set_device_num with the random device number and type
    acc_set_device_num(dev_num, dev_type);

    // Check that the device number was set correctly
    if (acc_get_device_num() != dev_num) {
        std::cout << "Error: acc_set_device_num did not set the device number correctly." << std::endl;
        err = 1;
    }

    // Check that the device type was set correctly
    if (acc_get_device_type() != dev_type) {
        std::cout << "Error: acc_set_device_num did not set the device type correctly." << std::endl;
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the results
    if (failcode != 0) {
        std::cout << "Error: acc_set_device_num failed." << std::endl;
    } else {
        std::cout << "Success: acc_set_device_num passed." << std::endl;
    }

    return failcode;
}