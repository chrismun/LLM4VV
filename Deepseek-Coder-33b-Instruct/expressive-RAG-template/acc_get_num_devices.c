#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc get num devices,V:2.7-3.3
int test1(){
    int err = 0;
    int num_devices = acc_get_num_devices(acc_device_nvidia);

    if(num_devices <= 0){
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