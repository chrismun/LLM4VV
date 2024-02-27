#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1:variable implicit data attributes,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 10;
    int a[size];
    int b = 0;

    // Initialize the array 'a'
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100; // Assign random values
    }

    // According to OpenACC specifications, the scalar variable 'b' inside the parallel region
    // should be treated as firstprivate if no other attributes are specified.
    #pragma acc parallel num_gangs(1)
    {
        for (int i = 0; i < size; i++) {
            b += a[i]; // Sum the array 'a' into 'b'
        }
    }

    int expected_b = 0;
    // Compute expected result for comparison
    for (int i = 0; i < size; i++) {
        expected_b += a[i];
    }

    if (b != expected_b) { 
        printf("Mismatch: GPU computed b = %d, expected b = %d\n", b, expected_b);
        err = 1; // Mark error if computation doesn't match
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    return failcode;
}