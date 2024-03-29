#include <openacc.h>
#include <iostream>

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    int async_arg = acc_async_sync;

    // Set the default async queue
    acc_set_default_async(async_arg);

    // Check if the default async queue has been set correctly
    if (acc_get_default_async() != async_arg) {
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