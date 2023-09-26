#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int main() {
    int failcode = 0;
    int failed;

    // Initialize the array on the host
    int n = 100;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    // Copy the array to the device
    real_t *d_a;
    acc_copyin(a, n * sizeof(real_t));

    // Update the values of the array on the device
    acc_update_device(d_a, n * sizeof(real_t));

    // Copy the updated array back to the host
    acc_copyout(a, n * sizeof(real_t));

    // Verify that the values of the array have been updated correctly
    for (int i = 0; i < n; i++) {
        if (fabs(a[i] - i) > PRECISION) {
            failcode = failcode + (1 << 0);
        }
    }

    // Free the memory on the device
    acc_free(d_a);

    return failcode;
}