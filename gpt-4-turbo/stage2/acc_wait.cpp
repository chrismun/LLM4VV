#include <iostream>
#include <vector>
#include <openacc.h>
#include <cstdlib>

#ifndef T1
// T1:acc_wait,V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // SEED for reproducibility

    const int N = 100;
    float* a = new float[N];
   
    // Initialize array
    for (int i = 0; i < N; ++i) {
        a[i] = i;
    }
   
    // Modify array in parallel asynchronously
    #pragma acc parallel loop async(1)
    for (int i = 0; i < N; ++i) {
        a[i] = a[i] * 2;
    }
   
    // Wait for the async operations to complete
    acc_wait(1);

    // Verify modifications
    for (int i = 0; i < N; ++i) {
        if (a[i] != i * 2) {
            err++;
        }
    }

    delete[] a;
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = test1();
    if (failed != 0) {
        failcode = failcode + 1;
    }
#endif
    return failcode;
}