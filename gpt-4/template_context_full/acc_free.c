#include "acc_testsuite.h"
#include <stdlib.h>

/*Test case for acc_free, using OpenACC Versions: 2.0-2.7*/
int test1(){
    int err = 0;
    /* Allocate some random data array */
    int * array = (int*) malloc(100 * sizeof(int));
    for (int i = 0; i < 100; i++)
        array[i] = i;

    /* Allocate device memory and copy data from host*/
    int* device_array = (int*)acc_malloc(100 * sizeof(int));
    acc_memcpy_to_device(device_array, array, 100 * sizeof(int));
    
    /* Now, free the allocated device memory */
    acc_free(device_array);
    
    /*Check if device pointer is not accessible after free operation*/
    if(acc_is_present(device_array, 100 * sizeof(int))){
        err = 1;  /* Memory is not freed properly */
    }

    /*Free allocated host memory*/
    free(array);
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