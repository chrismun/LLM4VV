#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();
    if (device_type != acc_device_nvidia) {
        // This test is only valid for NVIDIA GPUs
        return err;
    }

    int device_num = acc_get_device_num(device_type);
    acc_set_device_num(device_num, device_type);

    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = x;
        b[x] = 0;
    }

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc serial
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x] + 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != a[x] + 1){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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