#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *data = (int*)malloc(100 * sizeof(int));
    int *devicePtr;

    for(int i = 0; i < 100; i++) {
        data[i] = rand() % 100;
    }

    int condition = 1; //you can change this condition

    #pragma acc enter data create(devicePtr[0:100])
    
    if(condition) {
        #pragma acc host_data use_device(devicePtr) if(condition)
        {
            for(int i = 0; i < 100; i++) {
                devicePtr[i] = data[i];
            }
        }
    } else {
        for(int i = 0; i < 100; i++) {
            devicePtr[i] = data[i];
        }
    }

    for(int i = 0; i < 100; i++) {
        if(devicePtr[i] != data[i]) {
            err = 1;
            break;
        }
    }
    #pragma acc exit data delete(devicePtr)

    free(data);
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