#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1

int test_acc_get_default_async(){
    int err = 0;
    int default_async;

    default_async = acc_get_default_async();

    if(default_async != acc_async_noval){
        fprintf(stderr, "acc_get_default_async() failed: Expected %d, got %d\n", acc_async_noval, default_async);
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_get_default_async();
    }
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}