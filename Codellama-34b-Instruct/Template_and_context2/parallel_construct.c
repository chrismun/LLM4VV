#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct,V:2.7-3.3
int test1(){
    int err = 0;

    // create a parallel region with 4 gangs and 2 workers per gang
    #pragma acc parallel num_gangs(4) num_workers(2)
    {
        // create a reduction variable to store the sum of the values in the array
        int sum = 0;

        // create a loop to iterate over the array
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // add the value at the current index to the reduction variable
            sum += arr[i];
        }

        // store the reduction variable in the array
        arr[0] = sum;
    }

    // check that the reduction variable has the correct value
    if (arr[0] != 45) {
        err = 1;
    }

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