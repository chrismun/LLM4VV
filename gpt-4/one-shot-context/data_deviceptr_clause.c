#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

void test_deviceptr()
{
    int n = 100;

    // allocate host memory
    float* h_data = (float*) malloc(n*sizeof(float));

    // initialize the data
    for(int i=0; i<n; i++)
    {
        h_data[i] = 2.0f;
    }
  
    // allocate device memory
    float* d_data;
    d_data = (float*)acc_malloc(n*sizeof(float));

    // copy host data to device
    acc_memcpy_to_device(d_data, h_data, n*sizeof(float));

    // specify that d_data is a pointer to device memory
    #pragma acc data deviceptr(d_data)
    { 
        #pragma acc parallel loop 
        for (int i = 0; i < n; i++)
        {
            d_data[i] *= 2.0f;
        }
    }

    // copy results back to host
    acc_memcpy_from_device(h_data, d_data, n*sizeof(float));

    // check that the calculation was done correctly
    int error = 0;
    for(int i=0; i<n; i++)
    {
        if(fabs(h_data[i] - 4.0f) > 1e-5)
        {
            printf("Error at position %d: expected %f, got %f\n", i, 4.0f, h_data[i]);
            error++;
        }
    }

    if (error > 0)
    {
        printf("Test failed with %d errors\n", error);
    }
    else
    {
        printf("Test passed successfully\n");
    }

    // clean up
    acc_free(d_data);    
    free(h_data);
}

int main() 
{
    test_deviceptr();
    return 0;
}