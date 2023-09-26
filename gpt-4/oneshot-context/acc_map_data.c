#include <stdio.h>
#include <openacc.h>

#define N 1000

int main(){
    float *x = (float*) malloc(N*sizeof(float));  // Allocate on host
    float *d_x = (float*) acc_malloc(N*sizeof(float));  // Allocate on device

    // Initialize x array
    for(int i=0; i<N; i++)
        x[i] = 1.0f * i;

    // Copy host array to device
    acc_memcpy_to_device(d_x, x, N*sizeof(float));

    // Map device memory to host variable
    acc_map_data(x, d_x, N*sizeof(float));

    // Launch parallel region and use x
    #pragma acc parallel loop present(x[0:N])
    for(int i=0; i<N; i++){
        x[i] = x[i] * 2.0f;
    }

    // Unmap device memory
    acc_unmap_data(x);

    // Return device memory
    acc_free(d_x);

    // Print to check
    for(int i=0; i<10; i++)
        printf("%f\n", x[i]);

    free(x);

    return 0;
}