#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int main() {
    int failcode = 0;
    int failed;

    // Initialize variables
    int n = 10;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize data
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Create data region
    #pragma acc data copyin(a[0:n])
    {
        // Create kernel
        #pragma acc kernels
        {
            // Update variable in data region
            #pragma acc update self(b[0:n])
            {
                for (int x = 0; x < n; ++x) {
                    b[x] = a[x];
                }
            }
        }
    }

    // Check that variable has been updated correctly
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            failcode = failcode + (1 << 0);
        }
    }

    // Free memory
    free(a);
    free(b);

    return failcode;
}