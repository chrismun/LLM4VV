#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region with a single data element
    int data[1];
    data[0] = rand();

    // Create a second data region with a single data element
    int data2[1];
    data2[0] = rand();

    // Create an OpenACC data region with the first data element
    #pragma acc data copy(data[0])
    {
        // Create an OpenACC data region with the second data element
        #pragma acc data copy(data2[0])
        {
            // Verify that the data elements are not the same
            if (data[0] != data2[0]){
                err = 1;
            }
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