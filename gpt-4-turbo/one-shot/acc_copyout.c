#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM_TEST_CALLS 10
#define n 1000
#define SEED 42
#define PRECISION 0.0001
typedef float real_t;

int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

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
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    
    if (failed != 0) {
        failcode = failcode + (1 << 0);
        printf("Test Failed with %d errors.\n", failed);
    } else {
        printf("Test Passed.\n");
    }

    return failcode;
}