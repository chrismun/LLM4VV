#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    int global_var = 10;

    #pragma acc declare link(global_var)

    #pragma acc parallel copyin(global_var)
    {
        // Use the global variable in a compute region
        global_var += 1;
    }

    // Check if the global variable was correctly updated
    if (global_var != 11) {
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
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}