#include "acc_testsuite.h"

int main() {
    // Define a data array
    int data[100];
    
    // Initialize the data array with zeros
    #pragma acc parallel loop
    for(int i = 0; i < 100; i++) {
        data[i] = 0;
    }

    // Define error counter
    int error_count = 0;

    // Atomic increment test
    // Here each thread should atomically increment each element of the array "data".
    // Therefore we expect all elements of the array to be equal to "NUM_THREADS" after this region.

    #pragma acc parallel loop
    for(int i = 0; i < NUM_THREADS; i++) {
        #pragma acc loop 
        for(int j = 0; j < 100; j++) {
            #pragma acc atomic update
            data[j]++;
        }
    }

    // Check the results

    #pragma acc parallel loop reduction(+:error_count)
    for(int i = 0; i < 100; i++) {
        if(data[i] != NUM_THREADS)
            error_count++;
    }

    if(error_count != 0)
        printf("Test failed with %d errors! \n", error_count);
    else
        printf("Test passed successfully! \n");

    return 0;
}