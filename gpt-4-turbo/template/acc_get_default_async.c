#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"
#ifndef T1
// T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int default_async = acc_get_default_async();
    // Set a new default async value
    int new_async_value = (default_async + 1) % acc_async_noval; // Ensure it's a different and valid async value
    acc_set_default_async(new_async_value);

    // Verify if the default async has been set correctly
    if(acc_get_default_async() != new_async_value){
        err += 1; // Error if the retrieved default async does not match the set value
    }

    // Set it back to the original to clean up after the test
    acc_set_default_async(default_async);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
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