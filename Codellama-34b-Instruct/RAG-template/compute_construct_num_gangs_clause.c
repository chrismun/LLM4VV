#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the number of gangs to 2 in dimension 1
    #pragma acc parallel num_gangs(2)
    {
        // Do some work
    }

    // Set the number of gangs to 3 in dimensions 1 and 2
    #pragma acc parallel num_gangs(3, 3)
    {
        // Do some work
    }

    // Set the number of gangs to 4 in dimensions 1, 2, and 3
    #pragma acc parallel num_gangs(4, 4, 4)
    {
        // Do some work
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