#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int a[n];
    int i, sum = 0;
  
    for (i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(32) copyin(a)
    {
        int local_sum = 0;
        #pragma acc loop gang worker vector reduction(+:local_sum)
        for (i = 0; i < n; i++) {
            local_sum += a[i];
        }
        #pragma acc atomic
        sum += local_sum;
    }

    int expected_sum = 0;
    for (int i = 0; i < n; i++) {
        expected_sum += a[i];
    }

    if (sum != expected_sum) {
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