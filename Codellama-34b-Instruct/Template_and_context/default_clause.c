#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = rand();
    }

    // Set default data to be the first 50 elements of data
    int default_data[50];
    for (int i = 0; i < 50; i++) {
        default_data[i] = data[i];
    }

    // Set the default data for the reduction clause
    #pragma acc default(data)

    // Perform reduction on the default data
    int sum = 0;
    #pragma acc parallel loop reduction(+:sum)
    for (int i = 0; i < 50; i++) {
        sum += default_data[i];
    }

    // Check the result
    if (sum != 1275) {
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