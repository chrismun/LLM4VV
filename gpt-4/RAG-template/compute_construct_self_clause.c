#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#ifndef T1
//T1:compute construct self clause,V:2.7-3.3

int test1(){
    int err = 0;
    
    //Defining array size
    int N = 100; 
    float * a = (float *)malloc(N * sizeof(float));
    float * b = (float *)malloc(N * sizeof(float));
    
    //Initialising the arrays
    acc_init(acc_device_default);

    for (int i = 0; i < N; i++){
        a[i] = (float)i;
    } 

    // Use compute construct self clause  
    #pragma acc parallel loop self
    for (int i = 0; i < N; i++){
        b[i] = a[i]; 
    }

    // Check if the array is copied correctly 
    for (int i = 0; i < N; i++){
        if (a[i] != b[i]){
            err = 1;
            break;
        }
    }
    acc_shutdown(acc_device_default);
  
    return err;
}
#endif

int main(){
    int failed;
    int failcode = 0;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}