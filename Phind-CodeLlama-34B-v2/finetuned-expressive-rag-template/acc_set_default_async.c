#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int async_arg = rand() % 2;
    acc_set_default_async(async_arg);

    int async_arg_check = acc_get_default_async();

    if (async_arg_check != async_arg){
        err = 1;
        printf("acc_set_default_async failed. Expected: %d, Got: %d\n", async_arg, async_arg_check);
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