#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#define acc_get_default_async() acc_get_default_async_()

int acc_get_default_async_(void);

int test1(){
    int err = 0;
    srand(SEED);

    int default_async = acc_get_default_async_();

    if (default_async != acc_async_noval) {
        err = 1;
        printf("Test failed: acc_get_default_async returned %d, expected %d\n", default_async, acc_async_noval);
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}