#include "acc_testsuite.h"
#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    size_t bytes = PRESENT;
    if(acc_get_device_type() == acc_device_nvidia || acc_get_device_type() == acc_device_radeon){
        bytes = acc_get_property(acc_get_device_num(acc_get_device_type()), acc_property_free_memory);
    }

    int * a = (int *)acc_malloc(bytes);
    int i;

    if(bytes == 0){
        return 0;
    }
    if(a == NULL){
        return 1;
    }

    for(i = 0; i < bytes/sizeof(int); i++){
        a[i] = 1;
    }

    #pragma acc parallel copy(a[0:bytes/sizeof(int)]), loop
    for(i = 0; i < bytes/sizeof(int); i++){
        if(a[i] != 1){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}