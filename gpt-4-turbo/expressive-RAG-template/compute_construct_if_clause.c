#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h" // Assumed to provide SEED and NUM_TEST_CALLS

#ifndef T1
// T1:compute construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    float* a = (float*)malloc(size * sizeof(float));
    float* b = (float*)malloc(size * sizeof(float));
    float* c = (float*)malloc(size * sizeof(float));

    // Initialize vectors
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        c[i] = 0.0f;
    }

    // Perform conditionally parallel operation
    int condition = rand() % 2; // Randomly choose condition to be true or false
    #pragma acc parallel loop if(condition)
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }

    // Verification
    for (int i = 0; i < size; ++i) {
        if (condition && c[i] != a[i] + b[i]) {
            err++;
        } else if (!condition && c[i] != 0.0f) {
            // Ideally, values should remain unchanged if condition is false, indicating no parallel execution
            err++;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}