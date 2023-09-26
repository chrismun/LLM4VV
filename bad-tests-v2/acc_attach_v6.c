#include "acc_testsuite.h"
#include <stdlib.h>

int test_acc_attach_detach(){
    int err = 0;
    int* host_data = (int*)malloc(sizeof(int)*1000);
    int* dev_data = NULL;

    // initialize host data
    for(int i=0; i < 1000; i++){
        host_data[i] = i;
    }

    #pragma acc enter data create(dev_data[0:1000])

    // attach host pointer to device data
    acc_attach((void**)&dev_data);

    // Use device data 
    #pragma acc parallel loop present(dev_data[0:1000])
    for(int i=0; i < 1000; i++){
        dev_data[i] = dev_data[i] + 1;
    }

    // preemptively detach
    acc_detach((void**)&dev_data);

    //update host memory from device. 
    //If acc_detach worked correctly, this will give an error since dev_data should point to host memory
    #pragma acc update self(host_data[0:1000]) 

    // Check resulting data.
    for(int i = 0; i < 1000; ++i){
        if(host_data[i] != i + 1){
            err = 1;
            break;
        }
    }

    // Deallocate data region
    #pragma acc exit data delete(dev_data[0:1000])

    free(host_data);

    return err;
}

int main(){
    int failcode = 0;
    int failed = test_acc_attach_detach();
  
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
  
    return failcode;
}