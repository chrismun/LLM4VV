#include "acc_testsuite.h"
#include <stdlib.h>
#ifndef T1
//T1:compute construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int sum = 0;
    int a[NUM_ELEMENTS];
    int reduced_sum = 0;
    
    // filling up the array with random values
    for(int i=0; i<NUM_ELEMENTS; i++){
        a[i] = rand()%100;
        sum += a[i]; // calculating sum on host
    }
    
    #pragma acc parallel loop reduction(+:reduced_sum)
    for(int i=0; i<NUM_ELEMENTS; i++){
        reduced_sum += a[i]; // calculating sum on device using reduction clause
    }

    // check if both sums are equal
    if(sum != reduced_sum) {
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