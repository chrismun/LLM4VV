#include "acc_testsuite.h"
#ifndef T1
//T1:acc delete,V:2.7-3.3
int test1(){
    int err = 0;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    if (a == NULL || b == NULL) {
        printf("Failed to allocate memory for data arrays\n");
        return 1;
    }

    // Initialize data arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Transfer data to the device
    #pragma acc enter data copyin(a[0:N])

    // Perform computation on the device
    #pragma acc kernels
    {
        #pragma acc loop independent
        for (int i = 0; i < N; i++) {
            b[i] = a[i] * 2;
        }
    }

    // Delete data on the device
    #pragma acc exit data delete(a[0:N])

    // Verify correctness of the computation
    for (int i = 0; i < N; i++) {
        if (b[i] != i * 2) {
            printf("Incorrect result at %d: expected %d, got %d\n", i, i * 2, b[i]);
            err = 1;
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