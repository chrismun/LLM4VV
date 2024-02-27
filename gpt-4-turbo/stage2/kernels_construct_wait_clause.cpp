#include "acc_testsuite.h"
#ifndef T1
// T1:kernels construct wait clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    
    const int size = 10000;
    int * a = new int[size];
    int * b = new int[size];
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (float) RAND_MAX * 100;
        b[i] = 0;
    }
    
    #pragma acc kernels copyin(a[0:size]) copy(b[0:size])
    {
        #pragma acc loop independent
        for (int i = 0; i < size; ++i) {
            b[i] = a[i] + 1;
        }
    }
    #pragma acc wait
    
    #pragma acc kernels copyin(a[0:size]) copy(b[0:size])
    {
        #pragma acc loop independent
        for (int i = 0; i < size; ++i) {
            if (b[i] != a[i] + 1) {
                err = 1;
            }
        }
    }
    
    delete[] a;
    delete[] b;
    
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}