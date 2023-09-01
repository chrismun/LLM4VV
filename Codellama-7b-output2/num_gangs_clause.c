#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 2;
    int num_gangs_expected = num_gangs / num_workers;

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers)
    {
        int gang_id = acc_get_gang_id(0);
        if (gang_id != num_gangs_expected) {
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