#include "acc_testsuite.h"

#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1() {
    int err = 0;
    int num_elements = 1000;
    float *array = (float*)malloc(sizeof(float) * num_elements);
    srand(SEED);
    
    //Initialize array with parallel execution
    #pragma acc parallel loop copyout(array[0:num_elements]) 
    for(int i=0; i<num_elements; i++) {
        array[i] = (float)rand();
    }
    
    //Wait for completion of parallel execution
    #pragma acc wait
    
    //Check if the array was initialized correctly
    for(int i=0; i<num_elements; i++) {
        if(array[i] == 0.0) {
            err = 1; break;
        }
    }
    
    free(array); //Free memory
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}