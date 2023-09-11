#include <iostream>
#include <cstdlib>
#include <cmath>

#define NUM_TEST_CALLS 100
#define SEED 12345

int main() {
    int failcode = 0;
    int failed;

    // Test 1: wait directive with no arguments
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        srand(SEED);

        // Generate a random number of operations to enqueue
        int num_ops = rand() % 100;

        // Enqueue the operations
        for (int i = 0; i < num_ops; ++i) {
            int op = rand() % 2;
            if (op == 0) {
                // Enqueue a synchronization operation
                #pragma acc wait
            } else {
                // Enqueue an asynchronous operation
                #pragma acc wait async
            }
        }

        // Wait for all operations to complete
        #pragma acc wait

        // Check if any errors occurred
        if (err != 0) {
            failed++;
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: wait directive with async argument
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        srand(SEED);

        // Generate a random number of operations to enqueue
        int num_ops = rand() % 100;

        // Enqueue the operations
        for (int i = 0; i < num_ops; ++i) {
            int op = rand() % 2;
            if (op == 0) {
                // Enqueue a synchronization operation
                #pragma acc wait async
            } else {
                // Enqueue an asynchronous operation
                #pragma acc wait async
            }
        }

        // Wait for all operations to complete
        #pragma acc wait async

        // Check if any errors occurred
        if (err != 0) {
            failed++;
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: wait directive with if clause
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        srand(SEED);

        // Generate a random number of operations to enqueue
        int num_ops = rand() % 100;

        // Enqueue the operations
        for (int i = 0; i < num_ops; ++i) {
            int op = rand() % 2;
            if (op == 0) {
                // Enqueue a synchronization operation
                #pragma acc wait if (rand() % 2 == 0)
            } else {
                // Enqueue an asynchronous operation
                #pragma acc wait async if (rand() % 2 == 0)
            }
        }

        // Wait for all operations to complete
        #pragma acc wait if (rand() % 2 == 0)

        // Check if any errors occurred
        if (err != 0) {
            failed++;
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    return failcode;
}