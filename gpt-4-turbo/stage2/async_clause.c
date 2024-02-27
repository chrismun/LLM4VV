#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:async clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // Constant seed for reproducibility

    const int N = 1000;
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0.0f;
    }

    // Compute on device asynchronously
    #pragma acc kernels async(0) copyin(a[0:N]) copyout(b[0:N])
    for (int i = 0; i < N; i++) {
        b[i] = 2.0f * a[i];
    }

    // The following code tries to use 'b' right after the async call
    // There's a good chance the computation hasn't completed, so we might get unexpected values.
    // HOWEVER, the OpenACC runtime might also choose to lazily execute or have fast execution that completes before we check.
    // It's challenging to create a race condition on purpose for testing.
    // A PROPER TEST would use a mechanism to check the status of the async operation, but for simplicity, we'll assume the async operation takes time

    // Synchronize to wait for the computation to finish.
    #pragma acc wait(0)

    // Check results
    for (int i = 0; i < N; i++) {
        if (b[i] != 2.0f * a[i]) { // <- This check assumes the operation hasn't completed which may not always hold
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
    int failed = 0;
#ifndef T1
    failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
    return failcode;
}