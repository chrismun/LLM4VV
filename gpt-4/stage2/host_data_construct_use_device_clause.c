#include "acc_testsuite.h"
#ifndef T1
/*T1:host_data construct use_device clause,V:2.0-2.7*/
int test1(){
    int err = 0; 
    int * h_array;
    int h_array_size = 32;

    h_array = (int *)malloc(h_array_size * sizeof(int));

    srand(SEED);
    for(int i = 0; i < h_array_size; i++){
        h_array[i] = rand();
    }

    #pragma acc enter data create(h_array[0:h_array_size])

    // use_device clause tells the compiler to use the device address of h_array
    #pragma acc host_data use_device(h_array)
    {
        // If host_data construct use_device clause is working as expected, the device 
        // address of h_array should not be NULL and should be same as host address
        if(h_array == NULL){
            err = 1;
        }
    }

    #pragma acc exit data delete(h_array)

    // Cleanup and exit
    free(h_array);

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