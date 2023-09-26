#include "acc_testsuite.h"

#ifndef T1
/*T1:host_data construct use_device clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int* host_ptr = (int*) malloc(10 * sizeof(int));
    int* device_ptr;

    // Initialize host array
    for(int i=0; i<10; i++) {
        host_ptr[i] = rand() % 100;
    }

    // Allocate space on the device and copy data from the host
    #pragma acc enter data create(device_ptr[0:10])
    #pragma acc update device(device_ptr[0:10])

    // Use device_ptr inside host_data
    #pragma acc host_data use_device(device_ptr)
    {
      if(device_ptr == NULL){
        err = 1;
      }
    }

    // Deallocate space on the device
    #pragma acc exit data delete(device_ptr[0:10])

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