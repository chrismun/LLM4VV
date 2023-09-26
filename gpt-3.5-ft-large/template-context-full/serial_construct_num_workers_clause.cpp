#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int total_sum = 0;
    #pragma acc serial loop reduction(+:total_sum) num_workers(16)
    for (int i = 0; i < n; i++){
        total_sum += i;
    }


    return err;
}
#endif

#ifndef T2
//T2:serial construct combined with the parallel construct num_workers clause,V:2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);

    int total_sum = 0;

    #pragma acc serial loop reduction(+:total_sum) num_workers(8)
    for (int i = 0; i < n; i++){
        total_sum += i;
    }

    int original_total_sum = total_sum;

    #pragma acc parallel loop reduction(+:total_sum) num_workers(8)
    for (int i = 0; i < n; i++){
        total_sum += i;
    }

    if(original_total_sum  == total_sum){
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}