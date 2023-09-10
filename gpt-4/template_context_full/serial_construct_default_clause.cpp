#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct default clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int* arr_host;
    srand(SEED);
    if(getenv("ACC_DEVICE_TYPE") == NULL){
        arr_host = (int*)malloc(ARRAY_SIZE*sizeof(int));
    } else {
        acc_device_t device_type;
        if(strcmp(getenv("ACC_DEVICE_TYPE"), "nvidia") == 0){
            device_type = acc_device_nvidia;
        } else {
            device_type = acc_device_host;
        }
        acc_set_device_type(device_type);
        arr_host = (int*)acc_malloc(ARRAY_SIZE*sizeof(int));
    }

#pragma acc serial copyout(arr_host[0:ARRAY_SIZE]) default(none)
    for(int x = 0; x < ARRAY_SIZE; x++){
        arr_host[x] = x;
    }
    for(int x = 0; x < ARRAY_SIZE; x++){
        if(arr_host[x] != x){
            err = 1;
            break;
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}