#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a serial construct with a self clause
    acc_serial_construct(acc_self_clause);

    // Execute some code in the serial construct
    for (int i = 0; i < 10; i++) {
        std::cout << "Hello from the serial construct!" << std::endl;
    }

    // Check if the self clause was executed on the local device
    if (acc_self_clause) {
        std::cout << "The self clause was executed on the local device." << std::endl;
    } else {
        std::cout << "The self clause was not executed on the local device." << std::endl;
    }

    // Check if the self clause was executed on the current device
    if (acc_self_clause) {
        std::cout << "The self clause was executed on the current device." << std::endl;
    } else {
        std::cout << "The self clause was not executed on the current device." << std::endl;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}