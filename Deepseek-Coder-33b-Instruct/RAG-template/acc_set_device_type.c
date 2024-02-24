#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
#define T1
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();

    if(device_type != acc_device_default) {
        err = 1;
        printf("Error: Device type is not set correctly.\n");
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 10; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}