#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:serial construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int private_var = 0;

    #pragma acc parallel num_gangs(1) copy(private_var)
    {
        private_var = rand();
    }

    if (private_var != 0) {
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