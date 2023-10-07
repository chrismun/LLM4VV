#include "acc_testsuite.h"
#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int host_data[100];
    int * device_data = (int*)acc_malloc(100 * sizeof(int));
    
    acc_map_data(host_data, device_data, 100 * sizeof(int));
    if (!is_acc_deviceptr(device_data)){
        err = 1;
    }
    acc_unmap_data(host_data)
    acc_free(device_data);

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