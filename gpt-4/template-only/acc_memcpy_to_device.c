The above template needs to be filled in with an actual simulation involving OpenACC's memcpy. But note that it is important to have an OpenACC-enabled compiler such as 'pgcc' or 'gcc' with the OpenACC flag set which can understand and execute OpenACC commands.

#include "acc_testsuite.h"

#ifndef T1
/* T1:acc memcpy to device, V:2.7-3.3 */
int test1(){
    int err = 0;
    srand(SEED);
    int size = 10;
    float *h_array = (float*)malloc(sizeof(float)*size);
    float *d_array;

    /* Fill host array with random values */
    for(int i=0; i<size; i++) h_array[i] = (float)rand() / (float)RAND_MAX;

    /* Copy host array to device array */
    #pragma acc enter data create(d_array[0:size])
    acc_memcpy_to_device(d_array, h_array, sizeof(float)*size);

    /* Check if values of host array and device array are same */
    float temp[size];
    #pragma acc exit data copyout(temp[0:size])
    for(int i=0; i<size; i++){
        if(fabs(temp[i]-h_array[i] > 1e-5)) err = 1;
    }

    free(h_array);
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

Here, the test checks if the 'acc memcpy to device' kernel copies the correct values from the host array to the device array. The test will fail if there is a difference between the host and device values that is significant beyond machine precision. Note that I'm using simple floating point arithmetic for the example and it might need some modifications for your particular test environment and requirements.