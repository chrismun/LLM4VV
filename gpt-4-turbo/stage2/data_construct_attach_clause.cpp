#include <iostream>
#include <cstdlib>
#include <openacc.h>

// Function prototype for utility functions
void initializeArray(int* arr, int size);
bool verifyArray(int* arr, int size, int multiplier);

// Constants
const int ARRAY_SIZE = 100;
const int SEED = 42;
const int MULTIPLIER = 2;

// test1() function to evaluate the functionality of the attach clause
int test1(){
    int err = 0;
    srand(SEED);

    // Dynamic allocation of an array
    int* array = new int[ARRAY_SIZE];
    
    // Initialize array with random values
    initializeArray(array, ARRAY_SIZE);

    // Begin OpenACC region with an attach clause
    #pragma acc data copy(array[0:ARRAY_SIZE]) attach(array)
    {
        // Perform operations on array elements in parallel
        #pragma acc parallel loop
        for(int i = 0; i < ARRAY_SIZE; ++i)
        {
            array[i] *= MULTIPLIER;
        }
    }

    // Verifying the array's updated values
    if(!verifyArray(array, ARRAY_SIZE, MULTIPLIER))
    {
        err++;
    }

    // Cleanup
    delete[] array;

    return err;
}

// Utility function to initialize an array with random values.
void initializeArray(int* arr, int size)
{
    for(int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100; // Assign a random value between 0 and 99
    }
}

// Utility function to verify that each element of the array has been updated correctly.
bool verifyArray(int* arr, int size, int multiplier)
{
    for(int i = 0; i < size; ++i)
    {
        if(arr[i] % multiplier != 0)
        {
            return false; // If any element wasn't updated correctly, return false
        }
    }
    return true; // All elements were updated correctly
}

// Main function to execute test cases.
int main(){
    int failcode = 0;
    int failed;

    failed = test1();
    
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}