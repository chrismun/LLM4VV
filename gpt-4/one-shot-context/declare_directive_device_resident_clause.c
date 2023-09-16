#include <stdio.h>
#include <openacc.h>

#define N 100

#pragma acc declare device_resident(A)

int main() {
    int i, fail = 0;
    float A[N];

    /* Initialize array on the host */
    for (i = 0; i < N; ++i) A[i] = (float)i;

    /* Copy to device memory */
    #pragma acc update device(A[0:N])

    /* Compute on the device */
    #pragma acc parallel loop 
    for (i = 0; i < N; ++i) {
        A[i] = A[i] * 2.0f;
    }

    /* Copy back to host memory */
    #pragma acc update self(A[0:N])

    /* Check results */
    for (i = 0; i < N; ++i) {
        if (A[i] != i * 2.0f) {
            fail = 1;
            break;
        }
    }

    printf(fail ? "FAILED\n" : "PASSED\n");
    
    return 0;
}