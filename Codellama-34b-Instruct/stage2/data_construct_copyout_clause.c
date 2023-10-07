#include "acc_testsuite.h"

#ifndef T1
//T1:data construct copyout clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a structured data region with a copyout clause
    structured_data_region {
        int a;
        int b;
        int c;
    } data;

    // Initialize the data region
    data.a = 1;
    data.b = 2;
    data.c = 3;

    // Create a compute construct with a copyout clause
    #pragma acc parallel copyout(data)
    {
        // Do some work on the data region
        data.a += 1;
        data.b += 2;
        data.c += 3;
    }

    // Check that the data region has been copied out
    if (data.a != 2 || data.b != 4 || data.c != 6) {
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