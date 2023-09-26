#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

// array size
#define SIZE 1000

// function for initializing the array
void initialize(float* a, int size)
{
    for (int i = 0; i < size; i++)
        a[i] = (float) rand() / (float) (RAND_MAX/10.0);
}

// function for updating the array
void update(float* a, int size)
{
    #pragma acc parallel loop present(a[0:SIZE])
    for (int i = 0; i < size; i++)
        a[i] += 1.0;
}

int main()
{
    // declare array
    float* h_a = malloc(SIZE * sizeof(float));

    // initialize array values
    initialize(h_a, SIZE);
    
    // device memory allocation
    #pragma acc enter data create(h_a[0:SIZE])

    // update the array in device memory
    update(h_a, SIZE);

    // transfer the updated array from device memory to host memory
    #pragma acc exit data copyout(h_a[0:SIZE])

    // verify the results
    for (int i = 0; i < SIZE; i++) {
        if (abs((h_a[i] - 1)) > 1e-5){
            printf("TEST FAILED\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("TEST PASSED\n");
    return 0;
}