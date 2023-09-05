#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

// Declare a GPU kernel
#pragma acc routine seq
void gpu_kernel(float *arr, int n) 
{
    // Modify array values on the GPU
    #pragma acc loop gang
    for (int i = 0; i < n; i++) {
        arr[i] *= 2.0f;
    }
}

int main() 
{
    int n = 100;
    float *input = (float *)malloc(n * sizeof(float));

    // Initialize input array
    for (int i = 0; i < n; i++) {
        input[i] = i;
    }

    // Declare a device copy of the input array
    #pragma acc declare create(input[0:n])

    // Copy input array to the GPU
    #pragma acc update device(input[0:n])

    // Call the GPU kernel
    #pragma acc parallel
    {
        gpu_kernel(input, n);
    }

    // Copy the modified array back to the CPU
    #pragma acc update self(input[0:n])

    // Print the result
    for (int i = 0; i < n; i++) {
        printf("input[%d] = %f\n", i, input[i]);
    }

    // Free memory
    free(input);

    return 0;
}