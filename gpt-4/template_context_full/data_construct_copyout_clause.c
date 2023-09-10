#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct copyout clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int a = rand() % 10 + 1;
    int b;
    
    #pragma acc data copyout(b)
    {
        #pragma acc parallel present(b)
        {
            b = a;
        }
    }
    
    if(b != a){
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