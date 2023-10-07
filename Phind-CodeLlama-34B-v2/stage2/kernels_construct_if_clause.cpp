#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int device_type = acc_get_device_type();
    if (device_type != acc_device_nvidia) {
        return 0; // Skip the test if the device is not NVIDIA
    }

    int device_num = acc_get_device_num(device_type);
    acc_set_device_num(device_num, device_type);

    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() % n;
        b[x] = 0;
    }

    #pragma acc kernels if(device_num == 0)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            b[x] = a[x] + 1;
        }
    }

    for (int x = 0; x < n; ++x) {
        if (b[x] != a[x] + 1) {
            err = 1;
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