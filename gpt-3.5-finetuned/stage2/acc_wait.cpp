#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    #pragma acc data copy( a[0:10] )
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for( int x = 0; x < 10; ++x){
                a[x] = 1.0, + x;
            }
        }
        #pragma acc wait
        #pragma acc update host(a[0:10]) async(1)
    }
    for (int x = 0; x < 10; ++x){
        if (fabs(a[x] - x) > PRECISION){
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