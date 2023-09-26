#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Constants
#define ARRAY_SIZE 1000

// Test function for parallel implementation
bool test_parallel_openacc()
{
    int i;
    int* a = (int*) malloc(sizeof(int) * ARRAY_SIZE);

    //Initial input preparation
    for(i=0; i<ARRAY_SIZE; i++)
    {
        a[i] = i;
    }
    
    #pragma acc parallel loop copy(a[0:ARRAY_SIZE])
    for(i = 0; i < ARRAY_SIZE; i++)
    {
        a[i] = a[i] + 1; 
    }

    for(i = 0; i < ARRAY_SIZE; i++)
    {
        if(a[i] != i + 1)
        {
            return false;
        }
    }
    return true;
}

int main()
{   
    // flag to hold test result
    bool test_result;

    test_result = test_parallel_openacc();

    if(test_result == true){
        printf("Test Passed");
    }
    else{
        printf("Test Failed");
    }

    return 0;
}