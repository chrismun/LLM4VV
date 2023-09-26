#include "acc_testsuite.h"
#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 1000;
    float rand_nums[N];
    float target = 0.0, result = 0.0;
  
    // Fill array with random numbers and calculate their sum on the host
    for(int i=0; i<N; i++) {
        rand_nums[i] = (float)rand()/(float)(RAND_MAX/100.0);
        target += rand_nums[i];
    }

    #pragma acc parallel loop reduction(+:result)
    for(int i=0; i<N; i++) {
        result += rand_nums[i];
    }

    // Check if results match
    if(fabs(target - result) > 0.001){
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