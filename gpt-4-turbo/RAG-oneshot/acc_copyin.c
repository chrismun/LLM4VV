#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 0.001

typedef float real_t;

#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t* a = (real_t*) malloc(n * sizeof(real_t));
    real_t* b = (real_t*) malloc(n * sizeof(real_t));
    real_t* c = (real_t*) malloc(n * sizeof(real_t)); // Device side copy
    
    // Initialize array 'a' with random values and 'b' to zeros
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }
    
    // Allocate and copy 'a' to device, prepare 'b' on device without initializing
    #pragma acc enter data copyin(a[0:n]) create(c[0:n])
    #pragma acc parallel present(a[0:n], c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            c[x] = a[x]; // Copy 'a' to 'c' on device
        }
    }
    // Copy 'c' (device) back to 'b' (host)
    #pragma acc exit data copyout(b[0:n]) delete(c[0:n])
    
    // Verification
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 10; ++x) { // Assuming NUM_TEST_CALLS = 10
        int current_fail = test1();
        if (current_fail != 0) {
            printf("Test1 failed at iteration %d with %d errors.\n", x, current_fail);
            failed += current_fail;
        }
    }
    if (failed != 0) {
        failcode = 1;
    }
#endif
    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests have failed. Check log for details.\n");
    }
    return failcode;
}