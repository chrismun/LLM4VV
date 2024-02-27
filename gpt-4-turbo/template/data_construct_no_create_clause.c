#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    int *a = (int *)malloc(size * sizeof(int));
    int *b = (int *)malloc(size * sizeof(int));

    // Initialize array a with random data
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (RAND_MAX / 100);
    }

    // Copy data to GPU to simulate pre-existing data scenario
    #pragma acc enter data copyin(a[0:size])

    // Modify a on the host to check if no_create uses the device version without creating a new copy
    for (int i = 0; i < size; ++i) {
        a[i] = -1; // Set all elements to -1 on the host
    }

    // Run a parallel region on the GPU, annotate the data clause with no_create for array 'a'
    #pragma acc parallel loop no_create(a[0:size]) copyout(b[0:size])
    for(int i = 0; i < size; ++i){
        b[i] = a[i];  // Copy from 'a' to 'b' on the device
    }

    // Exit data from GPU, we do not need to update 'a' since we are checking 'b'
    #pragma acc exit data delete(a[0:size])

    // Check if 'b' contains the pre-modification values; if so, 'no_create' worked correctly
    for (int i = 0; i < size; ++i) {
        if (b[i] == -1) {
            err = 1; // Found an element of 'b' with post-modification value, indicating failure
            break;
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