#include "acc_testsuite.h"

#ifndef T1
/*T1:acc is present,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array with random numbers
    int num_elements = 10;
    int *array = (int*)malloc( num_elements * sizeof(int) );

    for(int i=0; i < num_elements; i++)
        array[i] = rand();
    
    // Check that the data is not present initially
    if ( acc_is_present( array, num_elements*sizeof(int)) ){
        err = 1;
    }

    // Copy data to device
    #pragma acc enter data copyin (array[0:num_elements])

    // Check that the data is present now
    if ( !acc_is_present( array, num_elements*sizeof(int)) ){
        err = 1;
    }

    // Delete from the device
    #pragma acc exit data delete (array)

    // Check that the data is not present now
    if ( acc_is_present( array, num_elements*sizeof(int)) ){
        err = 1;
    }

    // Clear allocated memory
    free(array);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}