#include "acc_testsuite.h"

//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_devices = acc_get_num_devices();
    if (num_devices == 0) {
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