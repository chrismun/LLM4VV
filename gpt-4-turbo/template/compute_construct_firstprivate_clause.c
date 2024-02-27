#include "acc_testsuite.h"
#ifndef T1
//T1:{parallel},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int test_val = rand(); // Initialize test variable with a random value.
    int *result_array = (int *)malloc(sizeof(int) * NUM_GANGS); // Array to store results per gang.

    // Initialize result array to a value that is different from test_val to check against.
    for(int i=0; i<NUM_GANGS; i++){
        result_array[i] = test_val - 1; // Ensure different initialization.
    }

    #pragma acc parallel num_gangs(NUM_GANGS) vector_length(1) copyout(result_array[0:NUM_GANGS]) firstprivate(test_val)
    {
        int gang_id = acc_gang_id();
        result_array[gang_id] = test_val; // Each gang sets its array element to test_val.
    }

    // Check if all gangs received the correct initial value.
    for(int i=0; i<NUM_GANGS; i++){
        if(result_array[i] != test_val){
            err++;
        }
    }

    free(result_array);

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