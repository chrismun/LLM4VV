#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int num_workers = 5;
    const int array_size = 100;
    int* test_array = (int*) malloc(sizeof(int) * array_size);

    // Initialize the array with zeros
    for (int i = 0; i < array_size; ++i) {
        test_array[i] = 0;
    }

    #pragma acc kernels num_workers(num_workers)
    for (int i = 0; i < array_size; ++i) {
        test_array[i] = i;
    }

    // Check the values in the array
    for (int i = 0; i < array_size; ++i) {
        if(test_array[i] != i){
            err = 1;
            break;
        }
    } 

    free(test_array);

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