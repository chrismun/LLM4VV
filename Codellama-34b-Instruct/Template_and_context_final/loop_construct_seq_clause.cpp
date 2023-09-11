#include <iostream>
#include <cstdlib>
#include <cmath>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Generate random data
    int n = 100;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    // Compute the sum of the elements in the array
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    // Check if the sum is correct
    if (sum != 100) {
        err = 1;
    }

    delete[] a;
    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}