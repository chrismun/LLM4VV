#include "acc_testsuite.h"
#include <stdlib.h>
#include <math.h>

int test_acc_update_device_self() {
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t)); // Allocating space for 'a'
    real_t * b = (real_t *)malloc(n * sizeof(real_t)); // Allocating space for 'b'

    // Filling 'a' with random values and setting 'b' to zero
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Copying into device memory
    #pragma acc enter data copyin(a[0:n])

    // Updating device data
    acc_update_device(a, n*sizeof(real_t));

    // Performing 'b = a' operation on device
    #pragma acc parallel loop present(a[0:n])
    for (int x = 0; x < n; ++x) {
        b[x] = a[x];
    }

    // Updating self
    acc_update_self(b, n*sizeof(real_t));

    // Comparing the two arrays
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_update_device_self();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }

    return failcode;
}