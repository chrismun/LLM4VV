#include <stdio.h>
#include <openacc.h>

#define SIZE 1000

int test1()
{
    int err = 0;
    float *hostArray;
    float *deviceArray;
    
    // Allocate memory on host
    hostArray = (float*) malloc(SIZE * sizeof(float));

    // Fill the array with some values
    for(int i = 0; i < SIZE; i++)
        hostArray[i] = i * 1.0;

    // Copy memory to device
    #pragma acc enter data copyin(hostArray[0:SIZE])

    // Get a device pointer from host pointer
    deviceArray = acc_deviceptr(hostArray);

    // Using acc_hostptr to get the pointer in host memory
    float *checkHostPtr = acc_hostptr(deviceArray);

    if( checkHostPtr != hostArray)
    {
        printf("acc_hostptr failed. The returned host pointer is not the same as the original.\n");
        err = 1;
    }

    // Free memory
    #pragma acc exit data delete(hostArray)
    free(hostArray);

    return err;
}

int main()
{
    int fail = 0;

    fail += test1(); 

    if (fail == 0) {
        printf("OpenACC acc_hostptr test passed.\n");
    } else {
        printf("OpenACC acc_hostptr test failed.\n");
    }

    return fail;
}