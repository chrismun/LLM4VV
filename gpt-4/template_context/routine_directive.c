#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Function to be tested
#pragma acc routine seq
void add_one(int *x) {
    #pragma acc atomic update
    *x += 1;
}

int main(int argc, char **argv) {

    int error = 0; // Flag to catch errors

    int *data;
    int size = 100;

    // Allocate memory
    data = (int*) malloc(size * sizeof(int));

    // Initialize to zero
    for(int i=0; i<size; i++)
        data[i] = 0;

    // Transfer data to device
    #pragma acc enter data copyin(data[0:size])

    // Call function in parallel region
    #pragma acc parallel loop
    for(int i=0; i<size; i++) {
        add_one(&data[i]);
    }

    // Transfer data back to host
    #pragma acc exit data copyout(data[0:size])

    // Verify results
    for(int i=0; i<size; i++) {
        if(data[i] != 1) {
            error = 1;
            printf("Error: data[%d] = %d, expected 1\n", i, data[i]);
        }
    }

    // Free memory
    free(data);

    // Return error flag
    return error;
}