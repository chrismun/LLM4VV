#include <iostream>
#include <stdlib.h>
#define SEED 12345
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    const int size = 1024;
    int *a = new int[size]; // Allocate memory for the array on the host
    int *b = new int[size]; // Auxiliary array to verify the result
    srand(SEED);

    // Initialize the array on the host
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100; // Fill with random values
        b[i] = a[i];         // Copy the values to verify later
    }

    // Use the OpenACC data construct to copy data to/from the device
    #pragma acc data copy(a[0:size])
    {
        // Inside the data region, modify the array 'a' on the device
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i){
            a[i] += 1;  // Each element incremented by 1 on the device
        }
    } // Data copied back to 'a' upon exit from the data region

    // Verify that the array 'a' was modified as expected
    for(int i = 0; i < size; ++i){
        if(a[i] != b[i] + 1){ // Check if 'a' was correctly incremented
            err = 1;  // Set error flag
            break;
        }
    }

    delete[] a; // Clean up dynamically allocated memory
    delete[] b;

    return err; // Return 0 if success, non-zero if there was an error
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    std::cout << "Test " << (failcode == 0 ? "PASSED" : "FAILED") << std::endl;
    return failcode;
}