#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    int a[100];
    int b[100];
    int i;

    // Initialize arrays
    for (i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Offload computation to GPU
    #pragma acc data copyin(a) copyout(b)
    {
        #pragma acc parallel loop device_resident(a)
        for (i = 0; i < 100; i++) {
            b[i] = a[i] * 2;
        }
    }

    // Check results
    for (i = 0; i < 100; i++) {
        if (b[i] != i * 2) {
            err = 1;
            break;
        }
    }

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