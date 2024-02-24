#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int global_var = 10;

    #pragma acc declare link(global_var)

    #pragma acc data copy(global_var)
    {
        #pragma acc kernels
        {
            global_var = 20;
        }
    }

    if (global_var != 20) {
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