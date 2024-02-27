#include "acc_testsuite.h"
#ifndef T1
//T1:{parallel},{async,wait},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a, *b;
    int async1 = 1, async2 = 2;

    a = (int*)malloc(size * sizeof(int));
    b = (int*)malloc(size * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // First parallel region, flagged with async1
    #pragma acc parallel loop async(async1)
    for (int i = 0; i < size; ++i) {
        a[i] = a[i] * 2;  // Some arbitrary operation
    }

    // Wait for the completion of the first parallel region
    #pragma acc wait(async1)

    // Second parallel region, depends on the first, using async2
    #pragma acc parallel loop async(async2)
    for (int i = 0; i < size; ++i) {
        b[i] = a[i] + 1;  // Operation that depends on the first
    }

    // wait for the second operation to finish
    #pragma acc wait(async2)

    // Verification
    for (int i = 0; i < size; ++i) {
        if (b[i] != (a[i] / 2) * 2 + 1) {  // Since a[i] was doubled
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