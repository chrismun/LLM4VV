#include "acc_testsuite.h"
#include <random>
#include <cmath>

#ifndef T1
/*T1:kernels construct num_gangs clause,V:2.0-2.7*/
int test1(){
    int err = 0;

    // Number of gangs
    const int numGangs = 100;

    // Create a large array to manipulate
    int data[numGangs];
    for (int i = 0; i < numGangs; ++i) {
        data[i] = i;
    }

    #pragma acc kernels num_gangs(numGangs)
    for(int i = 0; i < numGangs; ++i) {
        // The individual gangs should increment the data's respective index by 1.
        data[i]++;
    }

    //Check that each index has been incremented 
    for(int i = 0; i < numGangs; ++i){
        if(data[i] != i+1){
            err = 1;
        }
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