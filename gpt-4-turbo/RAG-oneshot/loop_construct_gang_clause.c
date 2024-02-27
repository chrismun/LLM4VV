#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#ifndef TEST_GANG
// TEST_GANG:parallel,loop,gang,V:1.0-3.1
int test_gang() {
    int err = 0;
    const int n = 1000;
    // Array to hold the gang ID each iteration is processed on
    int *gang_ids = (int *)malloc(n * sizeof(int));
    // Initialize array to -1 to easily spot unassigned spots (error detection)
    for (int i = 0; i < n; ++i) {
        gang_ids[i] = -1;
    }

    #pragma acc parallel num_gangs(10)
    {
        #pragma acc loop gang
        for (int i = 0; i < n; ++i) {
            // Assigning the gang ID to each element
            // Assuming an intrinsic or hypothetical function 'acc_get_gang_num()' for demonstration
            // Note: As of the knowledge cutoff in 2023, there's no direct way to access gang ID in OpenACC standard,
            // you might have to use vendor-specific mechanisms or approximations for actual test.
            gang_ids[i] = acc_get_gang_num();
        }
    }

    // Verify that divisions across gangs are made - simplistic check
    // In practice, more sophisticated validation might be required
    int found_in_different_gangs = 0;
    for (int i = 1; i < n; ++i) {
        if (gang_ids[i] != gang_ids[0]) {
            found_in_different_gangs = 1;
            break;
        }
    }

    if (!found_in_different_gangs) {
        // No distribution among gangs found
        err = 1;
    }

    free(gang_ids);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = test_gang();
    if (failed) {
        failcode = 1; // Bit position for TEST_GANG failure
    }

    if (failcode) {
        printf("Test FAILED with failcode %d.\n", failcode);
    } else {
        printf("All OpenACC gang clause tests PASSED.\n");
    }

    return failcode;
}