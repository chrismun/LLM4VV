#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Setting an explicit async queue might be required to change the default, but
    // for this test, we verify if it adheres to the initial default which should be 0.
    int default_async = acc_get_default_async();
    if (default_async != 0) {
        err += 1;
        printf("Error: Default async queue is not 0, but %d\n", default_async);
    }

    // Example to set and verify the change (optional)
    // Not directly part of OpenACC specification, but used to show practical usage
    /* acc_set_default_async(1);
     * default_async = acc_get_default_async();
     * if(default_async != 1){
     *     err += 1;
     *     printf("Error: After setting, default async queue is not 1, but %d\n", default_async);
     * }
     */

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