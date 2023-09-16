/* Including the required libraries */
#include "acc_testsuite.h"
#include <stdlib.h>

/* This is a simple test code to check proper functioning of host_data construct if_present clause */
int test1(){
    /* Initialize error counter to zero */
    int err = 0;

    /* Create a random data */
    float* host_array = (float*)malloc(100*sizeof(float));

    /* fill it with random data */
    for (int i=0; i<100; ++i)
        host_array[i] = (float) rand() / (float)(RAND_MAX);

    /* Use OpenACC to move the data in device memory */
    #pragma acc enter data create(host_array[0:100])

    /* Use if_present clause on host_data. It should not give an error because data is present on device. */
    #pragma acc host_data use_device(host_array) if_present
    {
        if(acc_is_present(host_array, 100*sizeof(float))){
            /* Do nothing because data is expected to be present on the device */
        } else {
            /* If data is not present raise an error flag */
            err = 1;
        }
    }

    /* Free used memory */
    free(host_array);

    /* return error flag. It should be zero if everything is fine */
    return err;
}

/* Main function to call the test multiple times and return a non-zero exit status in case of any failure */
int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}