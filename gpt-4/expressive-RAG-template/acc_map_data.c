#include "acc_testsuite.h"
#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    int a;
    int *d_a;
    srand(TIME_SEED);

    a = rand() % 50;
    #pragma acc data copy(a)
    {
        #pragma acc parallel 
        {
            d_a = &a;
        }
    }

    if(*d_a != a){
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