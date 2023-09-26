#include "acc_testsuite.h"

int test_openacc_create() {
    int err = 0;
    srand(SEED);
    real_t *g = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)calloc(n, sizeof(real_t));

    /* Initialize g */
    for (int x = 0; x < n; ++x) {
        g[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc declare create(c[0:n])

    /* Computing with g and storing results to c */
    #pragma acc parallel copyin(g[0:n]) copyout(c[0:n])
    {
        #pragma acc loop 
        for(int x = 0; x < n; ++x) {
            c[x] = g[x] * g[x];
        }
    }

    /* Verification of results */
    for(int x = 0; x < n; ++x) {
        real_t expected_result = g[x] * g[x];
        if(fabs(c[x] - expected_result) > PRECISION) {
            err++;
        }
    }

    free(g);
    free(c);

    return err;
}

int main() {
    int result = test_openacc_create();
    printf(result > 0 ? "Test FAILED\n" : "Test PASSED\n");
    return result;
}