#include "acc_testsuite.h"
#include <stdlib.h>

#define SIZE 100

#ifndef T1
/*T1:update directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int* host_array = (int*) malloc(SIZE * sizeof(int));
    int* device_array;

    // Initialize the host_array
    for(int i=0; i<SIZE; i++)
      host_array[i] = i;

    // alloc memory on device
    #pragma acc enter data create(device_array[0:SIZE])

    // copy array from host to device 
    #pragma acc update device(device_array[0:SIZE])

    // check if the array has been updated
    for(int i=0; i<SIZE; i++){
        if(device_array[i] != host_array[i]){
            err = 1;
        }
    }


    // update array from device back to host
    #pragma acc update self(host_array[0:SIZE])

    // check if the array has been updated
    for(int i=0; i<SIZE; i++){
        if(host_array[i] != device_array[i]){
            err = 1;
        }
    }

    free(host_array);
    #pragma acc exit data delete(device_array)

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