#include "acc_testsuite.h"

int test_if_present(){
    int err = 0;
    srand(SEED);
    int* hostArray = (int*)malloc(100*sizeof(int));
    int* deviceArray;
    
    // Initialize hostArray with some random data.
    for (int i=0; i<100; i++){
        hostArray[i] = rand();
    }
        
    #pragma acc enter data create(hostArray[0:100])
    #pragma acc host_data use_device(hostArray) if_present
    {
        deviceArray = hostArray; 
    }
    // Copy data back from device to host and compare.
    #pragma acc exit data copyout(hostArray[0:100])

    for (int i=0; i<100; i++) {
        if (hostArray[i] != deviceArray[i]) {
            err = 1;
            return err;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_if_present();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}