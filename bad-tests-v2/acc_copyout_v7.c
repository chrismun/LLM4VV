#include "acc_testsuite.h"
#ifndef T1
// T1: acc copyout, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int size = 100;
    int *input = (int *)malloc(size * sizeof(int));
    int *output = (int *)malloc(size * sizeof(int));

    // Initialize input array on the host
    for (int i = 0; i < size; i++) {
        input[i] = i;
    }

    // Allocate and copy input array to the device
    #pragma acc data copyin(input[0:size])
    {
        // Perform some computation on the device
        // ...

        // Copy output data from the device to the host
        #pragma acc host_data use_device(output)
        {
            #pragma acc copyout(output[0:size])
        }
    }

    // Verify if the output is correct
    for (int i = 0; i < size; i++) {
        if (output[i] != input[i]) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(input);
    free(output);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}