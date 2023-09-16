#include "acc_testsuite.h"
#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int vector[100];
    for (int i = 0; i < 100; ++i) vector[i] = rand();

    #pragma acc parallel loop copy(vector)
    for (int i = 0; i < 100; ++i) vector[i] *= 2;

    #pragma acc set async (0)
    int vector2[100];
    for (int i = 0; i < 100; ++i) vector2[i] = rand();

    #pragma acc parallel loop copy(vector2)
    for (int i = 0; i < 100; ++i) vector2[i] *= 3;

    #pragma acc wait

    for (int i = 0; i < 100; ++i){
        if (!(vector[i] % 2 == 0 && vector2[i] % 3 == 0)){
            err = 1;
            break;
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