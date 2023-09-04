#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a kernel with a single loop nest
    #pragma acc kernels
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with multiple loop nests
    #pragma acc kernels
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a conditional clause
    #pragma acc kernels if(condition)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a self clause
    #pragma acc kernels self(condition)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a copy clause
    #pragma acc kernels copy(var1, var2)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a copyin clause
    #pragma acc kernels copyin(var1, var2)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a copyout clause
    #pragma acc kernels copyout(var1, var2)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a create clause
    #pragma acc kernels create(var1, var2)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a no_create clause
    #pragma acc kernels no_create(var1, var2)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a present clause
    #pragma acc kernels present(var1, var2)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a deviceptr clause
    #pragma acc kernels deviceptr(var1, var2)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
        }
    }

    // Create a kernel with a default clause
    #pragma acc kernels default(none)
    for (int i = 0; i < 10; i++) {
        // Do some work
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            // Do some more work
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