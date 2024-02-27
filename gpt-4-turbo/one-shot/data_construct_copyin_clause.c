#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define real_t float
#define SEED 1234
#define n 10000
#define PRECISION 1e-5

int test_copyin_clause() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize array a with random values, array b set to 0
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Use OpenACC to copy array 'a' into the device at the beginning of the region and output to array 'b'
    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
    }

    // Check if the values have been correctly copied from 'a' to 'b'
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    return err;
}

int main() {
    int failed = test_copyin_clause();
    if (failed) {
        printf("Test failed with %d errors.\n", failed);
        return 1;
    } else {
        printf("Test passed.\n");
    }
    return 0;
}