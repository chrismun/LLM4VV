#include <stdio.h>
#include <openacc.h>

int main() {

    int size = 100;
    float *arr_host;
    arr_host = (float*) malloc(size*sizeof(float));

    // initialize host array
    for (int i = 0; i < size; i++) 
    {
        arr_host[i] = i+1.0;
    }

    float *arr_device;
    arr_device = (float*) acc_malloc(size*sizeof(float));

    // copy from host to device
    acc_memcpy_to_device(arr_device, arr_host, size*sizeof(float));
    
    // Compute on device with 'present' clause
    #pragma acc parallel present(arr_device[0:size])
    {
        #pragma acc loop
        for(int i=0; i<size; i++)
        {
            arr_device[i] *= 2.0;
        }
    }

    // copy result from device back to host
    acc_memcpy_to_host(arr_host, arr_device, size*sizeof(float));
    
    // Check Result
    for(int i=0; i<size; i++)
    {
        if(arr_host[i] != (i+1.0)*2.0) {
            printf("Error at position %d: expected %f, got %f\n", i, (i+1.0)*2.0, arr_host[i]);
            return -1;
        }
    }

    printf("Test Passed successfully!\n");
    return 0;