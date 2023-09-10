#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:attachment counter,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate device memory
    float * device_ptr = (float *)acc_malloc(10 * sizeof(float));
  
    // Register host data 
    float * host_ptr = new float[10];
    for (int i = 0; i < 10; i++) {
        host_ptr[i] = (float)rand()/(float)(RAND_MAX);
    }
    
    // Attach host pointer 
    acc_attach((void**)&device_ptr, host_ptr, 10 * sizeof(float));
    
    if(acc_is_present(device_ptr, 10 * sizeof(float)) != 1){
        err = 1;
    }

    // Detach host pointer
    acc_detach((void**)&device_ptr);
  
    if(acc_is_present(device_ptr, 10 * sizeof(float)) != 0){
        err = 1;
    }

    // Cleanup
    delete[] host_ptr;
    acc_free(device_ptr);

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