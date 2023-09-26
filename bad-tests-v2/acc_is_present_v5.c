#include <openacc.h>

int main() {
    int failcode = 0;
    int failed;

    // Test 1: acc_is_present with a null pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + acc_is_present(NULL, 0);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: acc_is_present with a non-null pointer
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int *data = (int *)malloc(sizeof(int));
        *data = 1;
        failed = failed + acc_is_present(data, sizeof(int));
        free(data);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: acc_is_present with a non-null pointer and a non-zero size
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int *data = (int *)malloc(sizeof(int));
        *data = 1;
        failed = failed + acc_is_present(data, sizeof(int));
        free(data);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    return failcode;
}