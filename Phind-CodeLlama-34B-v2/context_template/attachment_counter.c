#include "acc_testsuite.h"
#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    // Declare and allocate memory
    int *a = (int *)malloc(10 * sizeof(int));
    int *d_a = (int *)acc_malloc(10 * sizeof(int));

    // Initialize memory
    for (int x = 0; x < 10; ++x) {
        a[x] = rand() % 100;
    }

    // Copy data to device memory
    acc_memcpy(d_a, a, 10 * sizeof(int));

    // Attach and detach pointers multiple times
    for (int x = 0; x < 5; ++x) {
        acc_attach(d_a);
        acc_detach(d_a);
    }

    // Copy data back to host memory
    acc_memcpy(a, d_a, 10 * sizeof(int));

    // Check if the data was copied correctly
    for (int x = 0; x < 10; ++x) {
        if (a[x] != d_a[x]) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(a);
    acc_free(d_a);

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