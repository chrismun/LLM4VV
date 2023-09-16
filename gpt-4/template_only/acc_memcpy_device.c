#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Test: Copy array A to device, from HOST to DEVICE, and validate it
// Use OpenACC device_pointer attribute and acc_memcpy_device

#define SIZE 100

int main()
{
    int err = 0;
    int *A = (int*)malloc(SIZE*sizeof(int));

    // Initialize array on host
    for (int i=0; i<SIZE; i++)
        A[i] = i+1;

    // Copy to device
    int *d_A;
#pragma acc enter data create(d_A[0:SIZE])
    acc_memcpy_to_device((void*)d_A, (const void*)A, sizeof(int)*SIZE);

    // Test: Compare host and device array
    int *h_A = (int*)malloc(SIZE*sizeof(int));
    acc_memcpy_from_device((void*)h_A, (const void*)d_A, sizeof(int)*SIZE);

    for (int i=0; i<SIZE; i++){
        if(h_A[i] != A[i]){
            err = 1;
            break;
        }
    }
    free(A);
    free(h_A);
#pragma acc exit data delete(d_A)

    return err;
}