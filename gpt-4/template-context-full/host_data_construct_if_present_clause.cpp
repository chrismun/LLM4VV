#include "acc_testsuite.h"

/*T1:host_data construct if_present clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int* h_data;
    int* d_data;

    // Allocate space for host data and initialize with a random value.
    h_data = (int*)malloc(sizeof(int));
    *h_data = rand();

    // Allocate space in device memory for storing data.
#pragma acc enter data create(d_data[0:1])

    // Try to copy host_data to device memory.
#pragma acc update device(d_data[0:1]) if_present

#pragma acc host_data use_device(d_data)
    {
        // The address of d_data should be replaced by its device address.
        if(&d_data != &h_data){
            err += 1;
        }

        // Modifying the value of d_data.
        *d_data += 1;

        // Checking the updated value in the host.
        if(*h_data != (*d_data-1)){
            err += 1;
        }
    }

#pragma acc exit data delete(d_data[0:1])

    free(h_data);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Call the test1 method 'NUM_TEST_CALLS' times.
    failed = 0;
    srand(SEED);
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}