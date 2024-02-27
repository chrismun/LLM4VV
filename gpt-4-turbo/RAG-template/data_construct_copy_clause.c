#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1024
#define SEED 123
#define NUM_TEST_CALLS 10

int test1(){
    // Setup
    int err = 0;
    int *a, *b, *c;
    a = (int*) malloc(N * sizeof(int));
    b = (int*) malloc(N * sizeof(int));
    c = (int*) malloc(N * sizeof(int));

    // Initialize data
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0; // Ensure c is zeroed to test addition
    }

    #pragma acc data copy(a[0:N], b[0:N], c[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Verification
    for (int i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            err++;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        printf("Test Failed with %d errors.\n", failed);
        failcode = failcode + (1 << 0);
    } else {
        printf("Test Passed.\n");
    }
    return failcode;
}