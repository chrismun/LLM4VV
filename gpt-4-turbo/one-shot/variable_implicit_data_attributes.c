#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define n 1000
#define SEED 12345
#define PRECISION 0.00001
typedef float real_t;

#ifndef T_VAR_IMPLICIT
// T_VAR_IMPLICIT:kernels,data,data-region,V:1.0-2.7
int test_var_implicit() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t*)malloc(n * sizeof(real_t));
    real_t *implicit = (real_t*)malloc(n * sizeof(real_t)); // Implicitly should be treated by OpenACC

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        implicit[x] = 0; // Initialize array that should be implicitly managed.
    }

    // Only 'a' is explicitly copied in, expecting 'implicit' to be managed implicitly by the compiler/runtime.
    #pragma acc data copyin(a[0:n])
    {
        // Attempting operation on 'implicit' to see if it's managed correctly without explicit data clause.
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                implicit[x] = a[x] + 1;
            }
        }
    }

    // Verifying 'implicit' array has been updated as expected.
    for (int x = 0; x < n; ++x) {
        if (fabs(implicit[x] - (a[x] + 1)) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(implicit);

    return err;
}
#endif

int main() {
    int failcode = 0;

#ifndef T_VAR_IMPLICIT
    if (test_var_implicit() != 0) {
        failcode = failcode | (1 << 0);
        printf("Test for variable implicit data attributes failed.\n");
    } else {
        printf("Test for variable implicit data attributes passed.\n");
    }
#endif

    return failcode;
}