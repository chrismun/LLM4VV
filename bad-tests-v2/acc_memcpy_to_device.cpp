#include "acc_testsuite.h"
#include <cassert>

#ifndef T1
/*T1:acc memcpy to device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    size_t bytes = sizeof(int)*100;     // size for 100 integers
    int* host_data = (int *)malloc(bytes);    // allocate host memory
    int* dev_data = 
      (int *)acc_malloc(bytes);    // allocate device memory
    for (int i = 0; i < 100; ++i){
        host_data[i] = rand()%100;
    }

    acc_memcpy_to_device(dev_data, host_data, bytes);

    // check copied data
    for (int i = 0; i < 100; ++i){
        if (acc_memcpy_from_device(host_data[i], dev_data[i], sizeof(int)) != 0) {
            err = 1;
            break;
        }
    }
    // free the allocated memory
    acc_free(dev_data);
    free(host_data);
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