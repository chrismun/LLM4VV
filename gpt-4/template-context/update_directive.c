#include "acc_testsuite.h"

//Test update directive, V:2.7-3.3
int test1(){
    int err = 0;
    int *arr;
    int array_size = 1024;
    srand(SEED);
    
    arr = (int*)malloc(array_size*sizeof(int)); //allocate array

    //fill the array
    for (int i = 0; i < array_size; ++i) {
        arr[i] = i;
    }
    
    //Copy array to device
    #pragma acc enter data copyin(arr[0:array_size])

    //Update array on host
    for (int i = 0; i < array_size; ++i) {
        arr[i] = array_size - i;
    }
    
    //Update array on device with the new values from host
    #pragma acc update device(arr[0:array_size])
    
    //Update array on host from device to check correctness
    #pragma acc exit data copyout(arr[0:array_size])
    
    for (int i = 0; i < array_size; ++i){
        if (arr[i] != array_size - i){
            err = 1;
        }
    }
    
    free(arr); //Free allocated memory
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}