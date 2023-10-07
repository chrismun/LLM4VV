#include "acc_testsuite.h"

#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int a[10], b[10];
    bool match = true;

    // Initializing the array 'a' with random values and 'b' with zeros
    for (int i=0; i<10; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Copy 'a' to the device, compute and store the result in 'b' on the device, then copy the 'b' back to the host
    #pragma acc parallel copyin(a[0:10]) copyout(b[0:10])
    {
        #pragma acc loop
        for (int i=0; i<10; i++) {
            b[i] = a[i];
        }
    }
    
    // Check if values of 'a' and 'b' match
    for (int i=0; i<10; i++) {
        if(a[i] != b[i]) {
            match = false;
            break;
        }
    }

    if(!match){
        err = 1;
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