#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Allocate memory for device pointers
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize data on host
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Declare device pointers using data deviceptr clause
    #pragma acc data deviceptr(a, b)
    {
        // Copy data from host to device using kernels construct with copyout clause
        #pragma acc kernels copyout(b[0:n])
        {
            // Copy data from device to host using kernels construct with copyout clause
            #pragma acc kernels copyout(a[0:n])
            {
                // Verify that data has been copied correctly
                for (int x = 0; x < n; ++x) {
                    if (fabs(b[x] - a[x]) > PRECISION) {
                        failcode = 1;
                        break;
                    }
                }
            }
        }
    }

    // Free memory for device pointers
    free(a);
    free(b);

    return failcode;
}