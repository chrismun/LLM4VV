#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copyin(a[0:N])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < N; ++i) {
                a[i] = rand() % 100;
            }
        }

        #pragma acc compute wait
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int i = 0; i < N; ++i) {
                    a[i] *= a[i];
                }
            }
        }

        #pragma acc compute wait
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int i = 0; i < N; ++i) {
                    a[i] += 1;
                }
            }
        }

        #pragma acc compute wait
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int i = 0; i < N; ++i) {
                    a[i] -= 1;
                }
            }
        }
    }

    // Verify the result
    for (int i = 0; i < N; ++i) {
        int expected = ((a[i] * a[i]) + 1) - 1;
        if (a[i] != expected) {
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