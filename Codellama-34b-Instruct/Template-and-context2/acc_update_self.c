#include "acc_testsuite.h"
#ifndef T1
//T1:acc update self,V:2.7-3.3
int test1(){
    int err = 0;
    int data_arg[10];
    int bytes = sizeof(data_arg);

    // Initialize data_arg with some values
    for (int i = 0; i < 10; i++) {
        data_arg[i] = i;
    }

    // Call acc_update_self to update the data in local memory from the corresponding device memory
    acc_update_self(data_arg, bytes);

    // Check that the data in local memory has been updated
    for (int i = 0; i < 10; i++) {
        if (data_arg[i] != i) {
            err = 1;
            break;
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