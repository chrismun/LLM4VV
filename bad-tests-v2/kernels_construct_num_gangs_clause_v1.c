#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct num_gangs clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int numElements = 1024;
    const int gangs = 4;
    int host_array[numElements];
    int * device_array;

    // Allocate memory on the device
    device_array = (int *)acc_malloc(numElements * sizeof(int));

    // Populate array on the device with unique values per gang using OpenACC kernels and num_gangs clause
    #pragma acc kernels num_gangs(gangs)
    for(int i = 0; i < numElements; ++i) {
        device_array[i] = acc_gang_id(0);
    }

    // Copy data back to host
    #pragma acc update host(host_array[0:numElements])

    // Check if each section of the array contains the correct gang id 
    for(int i = 0; i < numElements; ++i) {
        if(host_array[i] != i / (numElements/gangs)){
            err = 1;          
            break;
        }
    }

    acc_free(device_array);
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