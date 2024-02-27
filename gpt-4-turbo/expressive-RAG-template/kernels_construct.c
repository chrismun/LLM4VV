#include <stdio.h>
#include <stdlib.h>

#define N 1000
#define SEED 123
#define NUM_TEST_CALLS 10

// Utility function to initialize array
void init_array(float* a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() / (float)RAND_MAX;
    }
}

// Test function for OpenACC kernels construct
int test_kernel_construct() {
    float *a, *b, *c;
    int err = 0;
    a = (float*)malloc(N * sizeof(float));
    b = (float*)malloc(N * sizeof(float));
    c = (float*)malloc(N * sizeof(float));

    // Initialize arrays
    srand(SEED);
    init_array(a, N);
    init_array(b, N);

    // Perform addition using OpenACC kernels
    #pragma acc kernels copyin(a[0:N],b[0:N]) copyout(c[0:N])
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Verify the result
    for(int i = 0; i < N; i++) {
        if(c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test_kernel_construct();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        printf("Kernels construct test: PASSED\n");
    } else {
        printf("Kernels construct test: FAILED\n");
    }

    return failcode;
}