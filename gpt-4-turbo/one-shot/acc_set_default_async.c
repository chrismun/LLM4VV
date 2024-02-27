#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define SEED 1234
#define n 1024
#define PRECISION 1e-5
#define DEFAULT_ASYNC_QUEUE 1

#ifndef T1
// T1:parallel,async,wait,V:1.0-2.7
int test_default_async() {
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (float)(RAND_MAX / 10);
        b[x] = 0;
    }

    acc_set_default_async(DEFAULT_ASYNC_QUEUE);

    #pragma acc parallel copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            b[x] = sqrtf(a[x]);
        }
    }

    // Wait for the default async queue to complete all operations.
    acc_wait(DEFAULT_ASYNC_QUEUE);

    for(int x = 0; x < n; ++x) {
        if(fabs(sqrtf(a[x]) - b[x]) > PRECISION){
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = test_default_async();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("PASSED: All tests passed!\n");
    } else {
        printf("FAILED: Some tests failed!\n");
    }

    return failcode;
}