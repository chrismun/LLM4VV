#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc get default async,V:2.7-3.3
int test1(){
    int err = 0;

    // Get the default async value
    int default_async = acc_get_default_async();

    // Check if the default async value is valid
    if (default_async != acc_async_sync && default_async != acc_async_noval) {
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}