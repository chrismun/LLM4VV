#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:compute construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();

    #pragma acc parallel loop self
    for (int i = 0; i < 100; i++) {
        if (device_type != acc_device_host) {
            err = 1;
        }
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