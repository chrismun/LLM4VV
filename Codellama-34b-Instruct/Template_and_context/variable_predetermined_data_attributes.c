#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable with predetermined data attributes
    int x = 0;

    // Set the data attributes for the variable
    acc_set_data_attributes(&x, ACC_DATA_ATTRIBUTE_PRIVATE);

    // Check that the data attributes are set correctly
    if (acc_get_data_attributes(&x) != ACC_DATA_ATTRIBUTE_PRIVATE) {
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