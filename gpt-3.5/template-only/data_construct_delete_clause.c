#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Perform some operations with OpenACC data constructs

    // Delete the OpenACC data constructs
    #pragma acc exit data delete(a,b,c)

    // Verify if the OpenACC data constructs are deleted
    if(a != NULL || b != NULL || c != NULL){
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