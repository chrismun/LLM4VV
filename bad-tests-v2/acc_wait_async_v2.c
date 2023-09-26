#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef T1
/*T1:acc wait async,V:2.0-2.7*/

int test1(){
    int err = 0;
    srand(SEED);

    //Initializes array a and b with the same random values
    float* a = (float*)malloc(1024*sizeof(float));
    float* b = (float*)malloc(1024*sizeof(float));
    for(int i=0;i<1024;i++){
        float random_value = (float)rand()/(float)(RAND_MAX);
        a[i] = random_value;
        b[i] = random_value;
    }

    //Perform a simple computation on device using array a
    #pragma acc parallel loop device_type(nvidia) async(1)
    for(int i = 0; i < 1024; i++) {
            a[i] *= 2.0f;
    }

    //Perform a simple computation on device using array b
    #pragma acc parallel loop device_type(nvidia) async(2)
    for(int i = 0; i < 1024; i++) {
            b[i] *= 2.0f;
    }

    //Wait for async queue 1 and 2 to complete their operations
    acc_wait_async(1, 2);

    //Verify that computations have been done correctly
    for(int i=0;i<1024;i++){
        if(a[i] != b[i]){
            err = 1; //err is 1 if there is an unexpected result
            break; 
        }
    }

    //Free memory
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