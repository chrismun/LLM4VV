#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc malloc
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int *a = (int *)acc_malloc(sizeof(int));
        if (a == NULL) {
            printf("acc_malloc failed\n");
            failed++;
        } else {
            *a = x;
            acc_free(a);
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}