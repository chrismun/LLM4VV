#include <iostream>
#include <cstdlib>
#include <cstring>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a compute construct with a default async queue
    int async_queue = 0;
    #pragma acc parallel num_gangs(1) async(async_queue)
    {
        // Do some work
        #pragma acc loop
        for (int i = 0; i < 100; i++) {
            // ...
        }
    }

    // Get the default async queue for the current thread
    int default_async_queue = acc_get_default_async();

    // Check that the default async queue is the same as the one we created
    if (default_async_queue != async_queue) {
        std::cerr << "Error: acc_get_default_async() returned the wrong async queue" << std::endl;
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure it passes consistently
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}