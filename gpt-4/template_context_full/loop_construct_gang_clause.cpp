#include "acc_testsuite.h"

#ifndef T1
int test1() {
    const int size = 1024;
    int err = 0;
    int *a = (int*)malloc(size * sizeof(int));
    
    srand(SEED);

    // Initialize array with random values
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
    }
    
    // Execute the loop in parallel
    #pragma acc parallel num_gangs(256) vector_length(4)
    {
        #pragma acc loop gang
        for(int i = 0; i < size; ++i) {
            a[i] *= 2;
        }
    }
    
    // Validate results
    for(int i = 0; i < size; ++i) {
        if(a[i] % 2 != 0) {
            err = 1;
            break;
        }
    }

    free(a);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if(failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}