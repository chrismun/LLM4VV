#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy to device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    size_t bytes = 1024;
    int *inputArray = (int*) malloc(bytes);
    for (int i = 0; i < bytes/sizeof(int); ++i) {
        inputArray[i] = rand();
    }
    int *devptr = (int*) acc_malloc(bytes);   
    if(devptr != NULL){
        acc_memcpy_to_device(devptr, inputArray, bytes);
        int *hostptr = (int*) malloc(bytes);
        acc_memcpy_from_device(hostptr, devptr, bytes);
  	    for (int i = 0; i < bytes/sizeof(int); ++i) {
            if(hostptr[i] != inputArray[i]){
            	err = 1;
            }
        }
        free(hostptr);
	acc_free(devptr);
    } else {
    	err = 1;
    }
    free(inputArray);

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