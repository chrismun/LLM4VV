#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef TEST01
/*TEST01: data construct no_create clause,V:2.7*/
int test(){
    int err = 0;
    int host_array[100], device_array[100];
    srand(SEED);

    // Initialize host array
    for(int i = 0; i < 100; i++){
        host_array[i] = rand()%100;
    }

#pragma acc data copy (device_array[:100])
#pragma acc parallel no_create (host_array[:100])
    {
        for(int i = 0; i < 100; i++){
            if (host_array[i] != 0) // Since host_array was not created on device, this should be zero 
                err = 1;
            device_array[i] = rand()%100;   // This should run without errors 
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef TEST01
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}