#include "acc_testsuite.h"
#ifndef T1
#define T1 1
//T1:update directive,V:2.7-3.3
int test1(){
    int err = 0;
    int a[50], b[50];

    // Initialize the arrays
    for (int i = 0; i < 50; i++){
        a[i] = rand() % 100;
    }

    //Copy data to the device
    #pragma acc enter data copyin(a[0:50], b[0:50])

    //Perform computation on the device
    #pragma acc parallel loop present(a[0:50], b[0:50])
    for (int i = 0; i < 50; i++){
        b[i] = a[i] * 2;
    }

    //Update a on host
    #pragma acc update host(a[0:50]) 

    //Check result
    for (int i = 0; i < 50; i++){
        if(a[i] != b[i]){
            err = 1;
        }
    }

    //Clean up
    #pragma acc exit data delete(a[0:50], b[0:50])
    
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