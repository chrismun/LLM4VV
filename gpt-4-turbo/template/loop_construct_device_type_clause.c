#include "acc_testsuite.h"
#ifndef T1
//T1:loop,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int sum_cpu = 0, sum_gpu = 0;

    // Initialize array with random data
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100; // Random numbers 0-99
        sum_cpu += a[i]; // Compute CPU sum for verification
    }

    #pragma acc parallel loop copyout(sum_gpu) device_type(nvidia)
    for (int i = 0; i < size; ++i) {
        sum_gpu += a[i];
    }

    // Assuming reduction is correctly implemented by the compiler,
    // sum_gpu should now contain the same value as sum_cpu if device_type worked.
    if (sum_gpu != sum_cpu) {
        err = 1; // Indicate error if values do not match
    }

    free(a); // Cleanup
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