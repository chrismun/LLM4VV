#include <stdlib.h>
#include "openacc.h"
#include "acc_testsuite.h"

//T1:acc create, device_type:host
int test1()
{
    int err = 0;
    srand(SEED);
    int* arr = (int*) malloc(100 * sizeof(int));

    // Filling array with data
    for(int i = 0; i < 100; i++)
    {
        arr[i] = rand();
    }
    
    // Creating data on the device
    #pragma acc enter data create(arr[0:100])

    // Checking if data is present on the device
    if(!acc_is_present(arr, 100 * sizeof(int)))
    {
        err = 1; 
    }

    // Delete data from the device
    #pragma acc exit data delete(arr[0:100])

    free(arr);
    return err;
}

int main()
{
    int failcode = 0;
    int failed;
    
    // Test "acc create"
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        failed = failed + test1();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}