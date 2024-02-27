#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>

#ifndef T1
// T1:shutdown,V:3.0
int test1() {
    int err = 0;
    const int n = 1024;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop copyout(b[0:n])
        for (int x = 0; x < n; ++x) {
            b[x] = a[x];
        }
        
        // Assuming the work here is representative
        // As of writing, using the shutdown directive explicitly is not common,
        // it's generally implicit in the termination of the program or when the runtime system decides.
        // However, we include it here for demonstration.
        #pragma acc shutdown
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > 1e-5) {
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
    failed = 0;
    for (int x = 0; x < 10; ++x) { // Example test calls; adjust as necessary.
        failed += test1();
    }
    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("PASSED: All tests.\n");
    } else {
        printf("FAILED: Code %d.\n", failcode);
    }

    return failcode;
}