#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc_free
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        void *data_dev = acc_malloc(10 * sizeof(int));
        if (data_dev == NULL) {
            printf("Failed to allocate memory on device\n");
            failed = 1;
            break;
        }
        acc_free(data_dev);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}