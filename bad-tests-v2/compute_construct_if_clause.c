#include "acc_testsuite.h"
#ifndef T1
// T1:compute construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int a = rand();
    int b = 0;
    #pragma acc parallel loop if(a%2==0) copy(a, b)
    for(int i=0; i<100; i++){
        b += a;
    }
    if(b != (a%2==0 ? a*100 : 0)){
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