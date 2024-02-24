#include <stdlib.h>
#include <openacc.h>

#define NUM_GANG_TEST 5

int test1(){
    int err = 0;
    int num_gangs = 0;

    #pragma acc parallel num_gangs(NUM_GANG_TEST)
    {
        num_gangs = acc_get_num_gangs();
    }

    if (num_gangs != NUM_GANG_TEST) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}