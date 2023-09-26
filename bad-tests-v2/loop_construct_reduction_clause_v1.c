#include "acc_testsuite.h"
#ifndef T1

//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    int num_elems = 1000;
    float a[num_elems];
    float reduction_sum = 0.0f;
    float expected_sum = 0.0f;
    srand(SEED);  

    for(int i=0;i<num_elems;i++){
        a[i] = (float)rand()/RAND_MAX;
	expected_sum += a[i];
    }

    #pragma acc parallel loop reduction(+:reduction_sum)
    for(int i=0; i<num_elems; i++){
        reduction_sum += a[i];
    }

    if(fabs(reduction_sum - expected_sum) > 1e-5){
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