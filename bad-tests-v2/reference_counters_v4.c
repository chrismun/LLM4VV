#include "acc_testsuite.h"

#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;

    // create a data region with a structured reference counter
    #pragma acc data copy(a[0:10])
    {
        // increment the structured reference counter
        #pragma acc enter data copyin(a[0:10])

        // create a data region with a dynamic reference counter
        #pragma acc data copy(b[0:10])
        {
            // increment the dynamic reference counter
            #pragma acc enter data copyin(b[0:10])

            // decrement the dynamic reference counter
            #pragma acc exit data copyout(b[0:10])

            // check that the reference counters are still non-zero
            if (acc_get_reference_count(a) != 1 || acc_get_reference_count(b) != 1) {
                err = 1;
            }
        }

        // decrement the structured reference counter
        #pragma acc exit data copyout(a[0:10])

        // check that the reference counters are still non-zero
        if (acc_get_reference_count(a) != 0 || acc_get_reference_count(b) != 0) {
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