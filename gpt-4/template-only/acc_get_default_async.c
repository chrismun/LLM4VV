#include "openacc.h"
#include "acc_testsuite.h"

#ifndef T1
//T1:acc get default async,V:2.7-3.3
int test1(){
    int result = 0;
    srand(SEED);

    int original_value = acc_get_default_async();
    
    // Setting a new default value    
    acc_set_default_async(5);

    // Check if getting the value we set
    if(acc_get_default_async() != 5){
        result = 1;
    }

    // Resetting to original
    acc_set_default_async(original_value);

    return result;
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