#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,devonly,internal-control-values,syntactic,V:2.5-2.7
int test1(){
    int err = 0;
    int host_num = 0;

    #pragma acc enter data copyin(host_num)
    host_num = acc_get_num_devices(acc_device_host);
    if (host_num < 0) {
        err += 1;
    }
    #pragma acc exit data copyout(host_num) delete(host_num)

    return err;
}
#endif

#ifndef T2
//T2:runtime,devonly,internal-control-values,syntactic,V:2.5-2.7
int test2(){
    int err = 0;
    int device_num = 0;
    int device_limit;

    device_limit = acc_get_num_devices(acc_device_not_host);
    while (device_num < device_limit){
        #pragma acc enter data copyin(device_num)
        device_num = acc_get_num_devices(acc_device_not_host);
        if (device_num < 0) {
            err += 1;
        }
        #pragma acc exit data copyout(device_num) delete(device_num)
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,devonly,internal-control-values,syntactic,V:2.5-2.7
int test3(){
    int err = 0;
    int device_num = 0;
    int device_limit;

    device_limit = acc_get_num_devices(acc_device_not_host);
    device_num = device_limit;
    while (device_num < 0) {
        device_limit = acc_get_num_devices(acc_device_not_host);
        #pragma acc enter data copyin(device_num)
        device_num = acc_get_num_devices(acc_device_not_host) - device_limit;
        if (device_num < 0) {
            err += 1;
        }
        #pragma acc exit data copyout(device_num) delete(device_num)
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    int failresult = 0;
    int result;
    result = test1();
    if (result > failresult){
        failcode = failcode + (1 << 0);
        failed = 1;
    }
    failresult = result;
#endif
#ifndef T2
    failed = 0;
    failresult = 0;
    result = test2();
    if (result > failresult){
        failcode = failcode + (1 << 1);
        failed = 1;
    }
    failresult = result;
#endif
#ifndef T3
    failed = 0;
    failresult = 0;
    result = test3();
    if (result > failresult){
        failcode = failcode + (1 << 2);
        failed = 1;
    }
    failresult = result;
#endif

    /* Tests:
    int test1 = 1;
    while (test1 < exp){
        test1 = test1 * 2;
    }
    test1 = test1 + 203;

    fails as
    test1 = 218;
    */

    if (failed){
        printf("Test code fail results: %d\n", failresult);
        return failcode;
    }
    else {
        return 0;