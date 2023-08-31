#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <accelerator.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate random data
    int *data1 = (int *)malloc(sizeof(int) * 100);
    int *data2 = (int *)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        data1[i] = rand();
        data2[i] = rand();
    }

    // Copy data using OpenACC
    int *data3 = (int *)malloc(sizeof(int) * 100);
    #pragma acc parallel loop present(data1[0:100], data2[0:100], data3[0:100])
    for (int i = 0; i < 100; i++) {
        data3[i] = data1[i] + data2[i];
    }

    // Check if the data is correct
    for (int i = 0; i < 100; i++) {
        if (data3[i] != (data1[i] + data2[i])) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(data1);
    free(data2);
    free(data3);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}