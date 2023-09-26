#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

#define N 1000000

// assuming a device function
__device__ float add_one(float a) { 
    return a+1;
}

int main() {
    float *a, *d_a;
    
    a = (float*)malloc(N*sizeof(float));

    // initializing the array
    for(int i=0; i<N; i++)
        a[i] = (float)i;

    // allocating device memory
    d_a = (float*)acc_malloc(N*sizeof(float));

    // copying data from host to device
    acc_memcpy_to_device(d_a, a, N*sizeof(float));

    // compute on the device
    #pragma acc parallel loop deviceptr(d_a)
    for(int i=0; i<N; i++) {
        d_a[i] = add_one(d_a[i]);
    }

    // copy the result back to the host
    acc_memcpy_from_device(a, d_a, N*sizeof(float));
    
    // check the result
    for(int i=0; i<N; i++) {
        if(a[i] != i+1) {
            printf("Validation failed at index %d. Got %f, expected %f\n", i, a[i], (float)(i+1));
            return 1;
        }
    }

    printf("Validation passed!\n");

    // freeing device and host memory
    acc_free(d_a);
    free(a);

    return 0;
}