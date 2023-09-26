#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1

int test_acc_get_default_async(){
    int err = 0;
    int default_async;

    default_async = acc_get_default_async();
    printf("Default async value: %d\n", default_async);

    if(default_async != 1 && default_async != 2){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_get_default_async();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}