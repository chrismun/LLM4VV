#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *a = (float*)malloc(size * sizeof(float));
    float *b = (float*)malloc(size * sizeof(float));

    // Initialize data
    for(int i = 0; i < size; ++i){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0f;
    }

    // Warm-up phase to ensure data in cache if possible
    #pragma acc data copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i){
            b[i] = 2 * a[i];
        }
    }

    // Test with cache directive
    for(int i = 0; i < size; ++i){
        a[i] = rand() / (float)RAND_MAX; // Reseed data to see impact of cache
    }

    #pragma acc data copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc parallel loop cache(a)
        for(int i = 0; i < size; ++i){
            b[i] = 2 * a[i];
        }
    }

    // Verify
    for(int i = 0; i < size; ++i){
        if (b[i] != 2*a[i]){
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}