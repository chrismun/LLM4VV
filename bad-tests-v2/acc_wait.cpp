#include "acc_testsuite.h"
#ifndef T1
/*T1:acc wait,V:2.0-2.7*/
int test1(){
    int err = 0;
    const int N = 10000;
    float *a = new float[N];
    float *b = new float[N];

    // Initialize data
    for(int i=0; i<N; i++)
    {
        b[i] = 1.0f * i;
    }

    // Create a parallel region and transfer array b to device
    #pragma acc enter data copyin(b[0:N])

    // Start calculating on device
    #pragma acc kernels async
    {
        for(int i=0; i<N; i++)
            b[i] = b[i] * 2;
    }

    // Wait for the async operation to complete using acc_wait
    #pragma acc wait

    // Transfer result from device
    #pragma acc exit data copyout(b[0:N])

    // Check results
    for(int i=0; i<N; i++)
    {
        if (b[i] != 2.0f * i){
            err = 1;
        }
    }

    // Free memory
    delete[] a;
    delete[] b;

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