#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int* data = (int*)malloc(sizeof(int));
    int* present_data = (int*)malloc(sizeof(int));

    // Initialize data and present_data
    for (int i = 0; i < 10; i++) {
        data[i] = i;
        present_data[i] = i;
    }

    // Use the present clause to ensure that data is present in the current device memory
    #pragma acc present(data)
    {
        // Perform some computation on data
        for (int i = 0; i < 10; i++) {
            data[i] += 1;
        }
    }

    // Use the present clause to ensure that present_data is present in the current device memory
    #pragma acc present(present_data)
    {
        // Perform some computation on present_data
        for (int i = 0; i < 10; i++) {
            present_data[i] += 1;
        }
    }

    // Check that data and present_data are equal
    for (int i = 0; i < 10; i++) {
        if (data[i] != present_data[i]) {
            err = 1;
            break;
        }
    }

    free(data);
    free(present_data);

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