#include "acc_testsuite.h"
#ifndef T1
//T1:async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int n = 1024;
    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));
    int* c = (int*)malloc(n * sizeof(int));
    int* seq = (int*)malloc(n * sizeof(int));

    // Initialize data on the host
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        seq[i] = a[i] + b[i]; // Reference computation
    }

    // Asynchronously copy data to the device in stream 1
    #pragma acc enter data copyin(a[0:n],b[0:n]) async(1)
    // Asynchronously perform vector addition on the device in stream 2
    #pragma acc parallel loop copyout(c[0:n]) async(2) wait(1)
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
    // Wait for all previous async operations in stream 2 to complete
    #pragma acc wait async(2)
    // Copy results back to the host synchronously (implicitly waits for all async operations to complete)
    #pragma acc exit data copyout(c[0:n])

    // Verify results
    for (int i = 0; i < n; ++i) {
        if (seq[i] != c[i]) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);
    free(seq);

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