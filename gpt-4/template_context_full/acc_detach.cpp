#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>

#ifndef T1
/*T1:acc detach,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    
    // create and initiate a pointer on host
    int* hostData = (int*) malloc(10*sizeof(int));
    for(int i = 0; i < 10; i++) {
        hostData[i] = i;
    }

    // create a pointer on the device
    int* deviceData = NULL;
#pragma acc enter data create(deviceData[0:10])

    //attach the host pointer to deviceData
#pragma acc enter data attach(hostData[0:10]) async(0)
    //from now, hostData on the host points to deviceData on the device
    acc_attach((void**)&hostData);

    //make sure data on the device finish their operations before detaching
#pragma acc parallel present(hostData)
    {
        for(int i=0; i<10; i++) {
            hostData[i] = hostData[i] + 1;
        }
    }
    acc_wait_all();

    //detach deviceData from the hostData
    acc_detach((void**)&hostData);

    //copy deviceData back to the host
#pragma acc exit data copyout(deviceData[0:10]) delete(deviceData)

    //check if acc_attach and acc_detach have been correctly used, the hostData should not be modified
    for(int i = 0; i < 10; i++) {
        if(hostData[i] != i) {
            err = 1;
        }
    }

    free(hostData);

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