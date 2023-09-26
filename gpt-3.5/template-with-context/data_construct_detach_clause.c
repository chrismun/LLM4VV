#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    int *a = (int *)malloc(10 * sizeof(int));
    
    // Generate data
    for (int i=0; i<10; i++) {
        a[i] = i;
    }
    
    int *b = (int *)malloc(10 * sizeof(int));
    
    #pragma acc data copyin(a[0:10]) copyout(b[0:10])
    {
        #pragma acc parallel loop detach
        for (int i=0; i<10; i++) {
            b[i] = a[i] * 2;
        }
    }

    // Verify the result
    for (int i=0; i<10; i++) {
        if (b[i] != (a[i] * 2)) {
            err = 1;
        }
    }
    
    free(a);
    free(b);
    
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += 1 << 0;
    }
#endif
    
    return failcode;
}